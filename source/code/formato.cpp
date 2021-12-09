#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include "../include/myUtil.h"
#include "../include/disco.h"
#include "../include/formato.h"

void Formato::formatdisk (char ** command, int num)
{
    FDISK_PARAM * mk = (FDISK_PARAM *)malloc(sizeof(FDISK_PARAM));
    mk -> size = 0;
    mk -> f = "wf";
    mk -> u = "k";
    mk -> type = "p";
    mk -> agregar = 0;

    std::string para;
    std::string token;
    std::string delimiter = "~:~";

    //este for es modelo de como se lleva a cabo el reconocimiento de opciones del comando
    for (int i = 2; i < num; i++){
        size_t pos = 0;
        para = std::string(MyUtil::aLower(command[i]));
        pos = para.find(delimiter);
        token = para.substr(0, pos);
        para.erase(0, pos + delimiter.length());

        if (token == "-path"){
            mk -> path = para;

        }else if (token == "-size"){
            mk -> size = stoi(para);

        }else if (token == "-unit"){
            if(para != "k" && para != "m" && para != "b"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< para << "\n";
                return;
            }
            mk -> u = para;

        }else if (token == "-fit"){
            if(para != "bf" && para != "ff" && para != "wf"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< para << "\n";
                return;
            }
            mk -> f= para;

        }else if (token == "-type"){ //pendiente de modificar
            if(para != "p" && para != "e" && para != "l"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< para << "\n";
                return;
            }
            mk -> type = para;

        }else if (token == "-delete"){//pendiente de modificar
            if(para != "fast" && para != "full"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< para << "\n";
                return;
            }
            mk -> borrar= para;


        }else if (token == "-name"){//pendiente de modificar
            mk -> name= para;

        }else if (token == "-add"){//pendiente de modificar
            mk -> agregar= stoi(para);

        }else{
            std::cout << "parametro no reconocido "<< token << "\n";
        }
    
    }
    //se verifican los obligatorios
    if(mk -> size == 0 && mk -> path.empty() && mk -> name.empty() ){
        printf("ERROR: parametros necesarios inexistentes\n");
        return;
    }

    if(mk->u == "b"){
        mk->size = mk->size;
        mk->agregar = mk->agregar;
    }else if(mk->u == "k"){
        mk->size = mk->size*1024;
        mk->agregar = mk->agregar*1024;
    } else if(mk->u == "m"){
        mk->size = mk->size*1024*1024;
        mk->agregar = mk->agregar*1024*1024;
    }
    mbr* algo = obtenerMBR ( mk );
    if ( mk ->type == "l"){
        definelogic( algo , mk);
    }else{
        definepart( algo , mk);
        displaymbr(algo);
    }
    
    
    
}

mbr* Formato::obtenerMBR (FDISK_PARAM * mk)
{
    mbr *diskmbr = (mbr *)malloc(sizeof(mbr));
    FILE *arch;
    arch= fopen(mk->path.c_str(), "rb");
    if (arch == NULL)
        exit(1);
    fseek(arch, 0, SEEK_SET);
    fread(diskmbr, sizeof(mbr), 1, arch);

    //displaymbr(diskmbr);
    return diskmbr;
}

void Formato::definepart (mbr * disk, FDISK_PARAM * mk)
{
    if (!mk -> agregar && mk -> borrar.empty()) {
        bool p_existe = false;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a crear
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                break;
            }

        }
        for( int i = 0; i < 4; i++){//revisamos si es extendida
            if(disk -> mbr_partition[i].part_type == 'e'){
                if(mk->type == "e"){
                    std::cout << "particion extendida ya existe\n";
                    return;
                }
            }

        }
        if ( p_existe){
            std::cout << "particion ya existente\n";
            return;
        }
        espaciodis n[6];
        freespace(disk, n); 
        bool sinpart = true;
        //para saber si existen o no particiones
        for( int i = 0; i < 4; i++){
            if (disk -> mbr_partition[i].part_size != 0 ){
                sinpart = false;
                break;
            }
        }
        //en el caso de que no hayan particiones
        if (sinpart) {
            //creamos info de la particion
            partition nueva;
            nueva.part_status = 0;
            nueva.part_type = mk->type[0];
            nueva.part_fit = mk->f[0];
            nueva.part_start = sizeof(mbr)+1;
            strcpy(nueva.part_name ,mk->name.c_str());
            nueva.part_size = mk->size;
            //almacenamos info en el mbr y escribimos
            disk ->mbr_partition[0] = nueva;
            escribirmbr(disk, mk->path.c_str());

            std::cout << "creacion de particioni exitosa\n";
            return;
        }
        //en el caso de que hayan particiones previas
        int inicio = sizeof(mbr);
        int size = 0;
        for( int i = 0; i < 6; i++){//procedemos con el calculo
            if (n[i].inicio <= 0 ){continue;}
            if ( disk -> disk_fit == 'f'){
                if ( n[i].size > (mk->size)){
                    inicio = n[i].inicio;
                    size = 1;
                    break;
                }

            } else if ( disk -> disk_fit == 'w'){
                if ( n[i].size > (mk -> size)){
                    if ( n[i].size > size ){
                        size = n[i].size;
                        inicio = n[i].inicio;
                    }
                }

            } else if ( disk -> disk_fit == 'b'){
                //std::cout << "llegaste a best fit\n";
                if ( n[i].size > (mk -> size)){
                    if ( 0 == size ){
                        size = n[i].size;
                        inicio = n[i].inicio;
                    }
                    if ( n[i].size < size ){
                        size = n[i].size;
                        inicio = n[i].inicio;
                    }
                }
            }
        }
        if (size == 0){
            std::cout << "cancelado por falta de espacio\n";
            return;
        }
        partition nueva;
        for( int i = 0; i < 6; i++){
            if(disk -> mbr_partition[i].part_size == 0){
                nueva.part_status = 0;
                nueva.part_type = mk->type[0];
                nueva.part_fit = mk->f[0];
                nueva.part_start = inicio+1;
                strcpy(nueva.part_name ,mk->name.c_str());
                nueva.part_size = mk->size;
                //almacenamos info en el mbr y escribimos
                disk ->mbr_partition[i] = nueva;
                escribirmbr(disk, mk->path.c_str());
                std::cout << "creacion de particioni exitosa posicionado\n";
                break;
            }
        }
        return;
    }
    else if ( mk -> agregar && mk->borrar.empty()){//parte para agregar
        bool p_existe = false;
        int posicion = 0;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a crear
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                posicion = i;
                break;
            }

        }
        if ( !p_existe){
            std::cout << "particion inexistente\n";
            return;
        }
        espaciodis n[6];
        freespace(disk, n); 
        //confirmar si se remueve un valor o se agrega
        std::cout << "estas en add\n";
        int finpart = (disk ->mbr_partition[posicion].part_start + disk ->mbr_partition[posicion].part_size);
        for( int i = 0; i < 6; i++){
            if (mk -> agregar > 0 ){ //es positivo se agrega espacio si existe espacio libre mayor a la cantidad a agregar
                if( finpart > n[i].inicio && mk ->agregar < n[i].size){
                    disk ->mbr_partition[posicion].part_size = mk ->agregar + disk ->mbr_partition[posicion].part_size;
                    std::cout << "agregando valor"<< mk->agregar<<"\n";
                    break;
                }
            } else if (mk -> agregar < 0 ) { //es negativo se retira espacio si no deja vacia la particion
                if( (disk ->mbr_partition[posicion].part_size +  mk ->agregar) > 0){
                    disk ->mbr_partition[posicion].part_size = mk ->agregar + disk ->mbr_partition[posicion].part_size;
                    std::cout << "reduciendo valor"<< mk->agregar<<"\n";
                    break;
                }
            } else {
                std::cout << "no puede ser cero\n";
            }
        }
        
        escribirmbr(disk, mk->path.c_str());
        std::cout << "add completado\n";
        return;

    } else if ( !mk -> agregar && !mk->borrar.empty()){//parte para borrar
        while ( true ){
            std::cout << "deseas eliminar el archivo s/n: \n";
            std::string confirmacion;
            std::cin >> confirmacion;
            if( confirmacion == "s")
                break;
            if ( confirmacion == "n")
                return;
        }
        

        bool p_existe = false;
        int posicion = 0;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a expandir
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                posicion = i;
                break;
            }
        }
        if ( !p_existe){
            std::cout << "particion inexistente\n";
            return;
        }
        disk -> mbr_partition[posicion].part_size = 0;
        disk -> mbr_partition[posicion].part_start = 0;
        strcpy(disk -> mbr_partition[posicion].part_name ,"jaja");
        disk -> mbr_partition[posicion].part_type = '-';
        if (mk -> borrar == "fast"){
             std::cout << "fast delete\n";
        }else if (mk -> borrar == "full"){
            std::cout << "full delete\n";
            FILE *arch;
            arch= fopen(mk->path.c_str(), "rb+");
            fseek(arch,disk -> mbr_partition[posicion].part_start,SEEK_SET);
            char n = '\0';
            fwrite(&n, disk -> mbr_partition[posicion].part_size, 1,arch);
            fclose(arch);

        }

        escribirmbr(disk, mk->path.c_str());
        std::cout << "delete completado\n";

    }else{
        printf("comando add, delete o crear no reconocido\n");
    }

}

void Formato::definelogic (mbr * disk, FDISK_PARAM* mk){
    if (!mk -> agregar && mk -> borrar.empty()) {
        bool p_existe = false;
        int pos = -1;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a crear
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                pos = i;
                break;
            }
        }
        
        if(disk -> mbr_partition[pos].part_type != 'e'){
            std::cout << "la particion no es extendida\n";
            return;
        }
        int start = disk -> mbr_partition[pos].part_start;
        int fin = disk -> mbr_partition[pos].part_size + start;

        partition logica;
        FILE *arch;
        arch= fopen(mk->path.c_str(), "rb+");
        fseek(arch, start, SEEK_SET);
        if ( disk -> mbr_partition[pos].part_next == -1){
            disk -> mbr_partition[pos].part_next = start;

            partition nueva;
            nueva.part_status = 0;
            nueva.part_type = mk->type[0];
            nueva.part_fit = mk->f[0];
            nueva.part_start = start;
            strcpy(nueva.part_name ,mk->name.c_str());
            nueva.part_size = mk->size;
            nueva.part_next = -1;
            escribirmbr(disk, mk->path.c_str());
            fwrite(&nueva, sizeof(partition), 1,arch);
            fclose(arch);
            std::cout << "particion logica creada\n";
            return;

        }
        else
        {
            while ( fread(&logica, sizeof(partition), 1, arch)){
                if ( logica.part_next == -1){
                    int sig = logica.part_start + logica.part_size;
                    int sig_size = sig + 1 + mk ->size + sizeof(partition);
                    if ( sig_size >= fin){
                        std::cout << "particion logica excede el espacio permitido\n";
                        return;
                    } 


                }else if (logica.part_size == 0) {//im sure the size is wrong
                    int sig = logica.part_start + logica.part_next;
                    int sig_size = sig + 1 + mk ->size + sizeof(partition);
                    if ( sig_size > fin){
                        fseek(arch, logica.part_next, SEEK_SET);
                        continue;
                    } 
                }else{
                    fseek(arch, logica.part_next, SEEK_SET);
                }
            }
        }

    }
    else if ( mk -> agregar && mk->borrar.empty()){//ADD:cambiar a logica
        bool p_existe = false;
        int posicion = 0;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a crear
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                posicion = i;
                break;
            }

        }
        if ( !p_existe){
            std::cout << "particion inexistente\n";
            return;
        }
        espaciodis n[6];
        freespace(disk, n); 
        //confirmar si se remueve un valor o se agrega
        std::cout << "estas en add\n";
        int finpart = (disk ->mbr_partition[posicion].part_start + disk ->mbr_partition[posicion].part_size);
        for( int i = 0; i < 6; i++){
            if (mk -> agregar > 0 ){ //es positivo se agrega espacio si existe espacio libre mayor a la cantidad a agregar
                if( finpart > n[i].inicio && mk ->agregar < n[i].size){
                    disk ->mbr_partition[posicion].part_size = mk ->agregar + disk ->mbr_partition[posicion].part_size;
                    std::cout << "agregando valor"<< mk->agregar<<"\n";
                    break;
                }
            } else if (mk -> agregar < 0 ) { //es negativo se retira espacio si no deja vacia la particion
                if( (disk ->mbr_partition[posicion].part_size +  mk ->agregar) > 0){
                    disk ->mbr_partition[posicion].part_size = mk ->agregar + disk ->mbr_partition[posicion].part_size;
                    std::cout << "reduciendo valor"<< mk->agregar<<"\n";
                    break;
                }
            } else {
                std::cout << "no puede ser cero\n";
            }
        }
        
        escribirmbr(disk, mk->path.c_str());
        std::cout << "add completado\n";
        return;

    } 
    else if ( !mk -> agregar && !mk->borrar.empty()){//REMOVE: cambiar a logica
        while ( true ){
            std::cout << "deseas eliminar el archivo s/n: \n";
            std::string confirmacion;
            std::cin >> confirmacion;
            if( confirmacion == "s")
                break;
            if ( confirmacion == "n")
                return;
        }
        

        bool p_existe = false;
        int posicion = 0;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a expandir
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                posicion = i;
                break;
            }
        }
        if ( !p_existe){
            std::cout << "particion inexistente\n";
            return;
        }
        disk -> mbr_partition[posicion].part_size = 0;
        disk -> mbr_partition[posicion].part_start = 0;
        strcpy(disk -> mbr_partition[posicion].part_name ,"jaja");
        disk -> mbr_partition[posicion].part_type = '-';
        if (mk -> borrar == "fast"){
             std::cout << "fast delete\n";
        }else if (mk -> borrar == "full"){
            std::cout << "full delete\n";
            FILE *arch;
            arch= fopen(mk->path.c_str(), "rb+");
            fseek(arch,disk -> mbr_partition[posicion].part_start,SEEK_SET);
            char n = '\0';
            fwrite(&n, disk -> mbr_partition[posicion].part_size, 1,arch);
            fclose(arch);

        }

        escribirmbr(disk, mk->path.c_str());
        std::cout << "delete completado\n";

    }
    else{
        printf("comando add, delete o crear no reconocido\n");
    }
}



void freespace ( mbr * disk, espaciodis blancos[]){
    espaciodis aux[6];
    espaciodis vacio;
    vacio.inicio = 0;
    vacio.size = 0;
    for (int i = 0; i < 6; i++ ) {//recuperamos tamanios e inicios del mbr
        if(disk -> mbr_partition[i].part_size != 0 && i-1 < 4){
            aux[i].inicio = disk ->mbr_partition[i].part_start;
            aux[i].size = disk ->mbr_partition[i].part_size;
        } else if(i == 5){
            aux[i].inicio = 0;
            aux[i].size = sizeof(mbr);
        }else { aux[i] = vacio;}
    }
    verlibre(aux);
    std::sort(aux, aux + 6, espaciodis::order);
    verlibre(aux);
    int lastpos = sizeof(mbr)+1;
    int posv = 0;
    espaciodis nuevo;
    nuevo.inicio = 0;
    nuevo.size = 0;
    for (int i = 0; i < 6; i++){
        if (aux[i].inicio == 0 && aux[i].size ==0){
            continue;
        }else if ( i == 5 ){
            lastpos = aux[i].inicio + aux[i].size;
            nuevo.inicio = lastpos;
            nuevo.size = disk ->size - lastpos;
            blancos[posv] = nuevo;
            break;
        }else if ( i < 5 ){
            lastpos = aux[i].inicio + aux[i].size;
            nuevo.inicio = lastpos;
            nuevo.size = aux[i+1].inicio - lastpos;
            blancos[posv] = nuevo;
            posv++;
        }
    }
   verlibre(blancos);

}

void verlibre (espaciodis aux[]){
    for (int i = 0; i < 6; i++){
        std::cout<< aux[i].inicio << " "<<aux[i].size << "\n";
    }
     std::cout << "hola "<< "\n";
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include "../include/myUtil.h"
#include "../include/disco.h"
#include "../include/formato.h"
#include "../include/filesis.h"

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
        int posi = 0;
               while ((posi = para.find(' ')) != std::string::npos) {
                    para.replace(posi, 1, "_");
               }
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

        }else if (para[0] == '#' || para[0] == '/'){
            std::cout<<"\033[92m" <<para << "\033[0m\n";
            break;
        }else{
            printf("tipo de parametro desconocido\n");
            return;
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
        //displaymbr(algo);
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
        strcpy(disk -> mbr_partition[posicion].part_name ,"ja");
        disk -> mbr_partition[posicion].part_type = '-';
        if (mk -> borrar == "fast"){
             std::cout << "fast delete\n";
        }else if (mk -> borrar == "full"){
            std::cout << "full delete\n";
            FILE *arch;
            arch= fopen(mk->path.c_str(), "rb+");
            fseek(arch,disk -> mbr_partition[posicion].part_start,SEEK_SET);
            char n = '\0';
            for ( int i = 0; i < disk -> mbr_partition[posicion].part_size; i++){
                fwrite(&n, sizeof(n), 1,arch);
            }
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
            if(disk -> mbr_partition[i].part_type == 'e'){
                p_existe = true;
                pos = i;
                break;
            }
        }
        
        if(!p_existe){
            std::cout << "no existe particion extendida\n";
            return;
        }
        int start = disk -> mbr_partition[pos].part_start;
        int fin = disk -> mbr_partition[pos].part_size + start;
        if( fin <= (start + sizeof(partition) + mk->size)){
            std::cout << "particion logica demasido grande\n";
            return;
        }

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
            nueva.part_start = start+sizeof(partition)+1;
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
            int startlogic = start;
            fread(&logica, sizeof(partition), 1, arch);
            do{
                
                if ( logica.part_next == -1){
                    int sig = logica.part_start + logica.part_size;
                    int sig_size = sig + 1 + mk ->size + sizeof(partition);
                    if ( sig_size >= fin){
                        std::cout << "particion logica excede el espacio permitido\n";
                        return;
                    } 
                    if (logica.part_name == mk ->name){
                        std::cout << "particion logica excede el espacio permitido\n";
                        return;
                    }
                    
                    logica.part_next = sig +1;
                    //displaypart(logica);
                    //std::cout << "particion nueva";
                    
                    fseek(arch, startlogic, SEEK_SET);
                    fwrite(&logica, sizeof(partition), 1,arch);

                    {fseek(arch, sig+1, SEEK_SET);
                    partition nueva;
                    nueva.part_status = 0;
                    nueva.part_type = mk->type[0];
                    nueva.part_fit = mk->f[0];
                    nueva.part_start = sig+1+sizeof(partition);
                    strcpy(nueva.part_name ,mk->name.c_str());
                    nueva.part_size = mk->size;
                    nueva.part_next = -1;
                    displaypart(nueva);
                    fwrite(&nueva, sizeof(partition), 1,arch);
                    fclose(arch);
                    std::cout << "particion logica creada\n";}
                    return;

                }else if (logica.part_size == 0) {//what am i tryin' to do???
                    int limlibre = logica.part_next;
                    int sig_size = logica.part_start+ mk ->size + sizeof(partition)+1;
                    if ( sig_size >= limlibre || sig_size >= logica.part_next){
                        startlogic = logica.part_next;
                        fseek(arch, logica.part_next, SEEK_SET);
                        continue;
                    } 
                    if (logica.part_name == mk ->name){
                        std::cout << "particion logica excede el espacio permitido\n";
                        return;
                    }
                    logica.part_status = 0;
                    logica.part_type = mk->type[0];
                    strcpy(logica.part_name ,mk->name.c_str());
                    logica.part_fit = mk->f[0];
                    logica.part_size = mk->size;
                    displaypart(logica);
                    fwrite(&logica, sizeof(partition), 1,arch);
                    fclose(arch);
                    std::cout << "particion logica creada\n";
                    return;
                } else{
                    //std::cout << "part logica actual\n";
                    //displaypart(logica);
                    startlogic = logica.part_next;
                    fseek(arch, logica.part_next, SEEK_SET);
                    fread(&logica, sizeof(partition), 1, arch);
                }
            }while ( startlogic != -1 );
        }
        std::cout << "no existe la particion logica\n";

    }
    else if ( mk -> agregar && mk->borrar.empty()){//ADD:cambiar a logica
        bool p_existe = false;
        int pos = -1;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a crear
            if(disk -> mbr_partition[i].part_type == 'e'){
                p_existe = true;
                pos = i;
                break;
            }
        }
        
        if(!p_existe){
            std::cout << "no existe particion extendida\n";
            return;
        }
        int start = disk -> mbr_partition[pos].part_start;
        int fin = disk -> mbr_partition[pos].part_size + start;
        FILE *arch;
        arch= fopen(mk->path.c_str(), "rb+");
        fseek(arch, start, SEEK_SET);
        partition logica;
        int startlogic = start;
        fread(&logica, sizeof(partition), 1, arch);
        do{
            displaypart(logica);
                if ( logica.part_name == mk ->name){
                    int newsize = logica.part_size + logica.part_start + mk ->agregar;
                    if (logica.part_next == -1) {
                        if ( newsize >= fin){
                            std::cout << "particion logica excede el espacio permitido\n";
                            return;
                        }
                    } else if (newsize >= logica.part_next){
                        std::cout << "particion logica excede el espacio permitido\n";
                        return;
                    } else if ( newsize <= 0){
                        std::cout << "particion logica menor al espacio permitido\n";
                        return;
                    }
                    logica.part_size = logica.part_size + mk ->agregar;
                    displaypart(logica);
                    fwrite(&logica, sizeof(partition), 1,arch);
                    fclose(arch);
                    std::cout << "particion logica modificada\n";
                    return;
                } else{
                    //std::cout << "part logica actual\n";
                    //displaypart(logica);
                    startlogic = logica.part_next;
                    fseek(arch, logica.part_next, SEEK_SET);
                    fread(&logica, sizeof(partition), 1, arch);
                
                }
        }while ( startlogic != -1 );
        std::cout << "no existe la particion logica\n";
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
        int pos = -1;
        for( int i = 0; i < 4; i++){//revisamos si exite la particion a crear
            if(disk -> mbr_partition[i].part_type == 'e'){
                p_existe = true;
                pos = i;
                break;
            }
        }
        
        if(!p_existe){
            std::cout << "no existe particion extendida\n";
            return;
        }
        int start = disk -> mbr_partition[pos].part_start;
        int fin = disk -> mbr_partition[pos].part_size + start;
        FILE *arch;
        arch= fopen(mk->path.c_str(), "rb+");
        fseek(arch, start, SEEK_SET);
        partition logica;
        int startlogic = start;
        fread(&logica, sizeof(partition), 1, arch);
        do{
                displaypart(logica);
                if ( logica.part_name == mk ->name){
                    
                    if ( mk -> borrar == "fast"){
                        std::cout << "fast delete\n";
                    } else if ( mk -> borrar == "full"){
                        int tamelim = logica.part_size;
                        std::cout << "full delete\n";
                        fseek(arch,logica.part_start,SEEK_SET);
                        char n = '\0';
                        for (int i = 0; i < tamelim; i++){
                            fwrite(&n, sizeof(n), 1,arch);
                        }
                    }
                    logica.part_size = 0;
                    strcpy(logica.part_name ,"ja");
                    fwrite(&logica, sizeof(partition), 1,arch);
                    fclose(arch);
                    std::cout << "particion logica eliminada\n";
                    return;
                }else{
                    //std::cout << "part logica actual\n";
                    //displaypart(logica);
                    startlogic = logica.part_next;
                    fseek(arch, logica.part_next, SEEK_SET);
                    fread(&logica, sizeof(partition), 1, arch);
                
                }
        }while ( startlogic != -1 );
        std::cout << "no existe la particion logica\n";
    }
    else{
        printf("comando add, delete o crear no reconocido\n");
    }
}

void Formato::writesb (FILE * arch, int posicion){
    sblock* superb = new sblock();
    superb->s_fs_type = 2;//2 o 3
    superb->s_in_count=0;//numero de inodos
    superb->s_ib_count=0;//numero de bloques
    superb->s_fb_count=0;//numero de bloques vacios
    superb-> s_fi_count=0;//numero de nodos vacios
    superb-> s_mtime =time(0);;//fecha ultimo montaje
    superb->s_umtiem =time(0);;//fecha de unmount
    superb->s_mnt_cout =0;//conteo de mount
    superb->s_magic = 0xEF53;//numero magico
    superb->s_in_size = sizeof(inode);//tama;o del inodo
    superb->s_ib_size = 64;//tama;io del bloque
    superb->s_first_in=0;//primer inodo libre
    superb->s_first_ib=0;//primer bloque libre
    superb->s_bm_inode_s= 0;//inicio del bitmap de inodos
    superb->s_bm_iblock_s=0;//inicio del bitmap de bloques
    superb->s_in_start=0;//inicio de inodos
    superb->s_ib_start=0;//inicio de bloques
    fseek(arch, posicion, SEEK_SET);
    fwrite(superb, sizeof(sblock), 1, arch);

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
    //verlibre(aux);
    std::sort(aux, aux + 6, espaciodis::order);
    //verlibre(aux);
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
   //verlibre(blancos);

}

void verlibre (espaciodis aux[]){
    for (int i = 0; i < 6; i++){
        std::cout<< aux[i].inicio << " "<<aux[i].size << "\n";
    }
     std::cout << "hola "<< "\n";
}
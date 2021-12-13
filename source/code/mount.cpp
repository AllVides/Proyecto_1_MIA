#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include "../include/myUtil.h"
#include "../include/disco.h"
#include "../include/formato.h"
#include "../include/mount.h"


void part_montar ( int num,char** command){
    std::string para;
    std::string ruta;
    std::string nombre;
    std::string token;
    std::string delimiter = "~:~";

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
            ruta = para;
        } else if (token == "-name"){
            nombre = para;
        }else {
            std::cout << "ERROR: parametro no permitido\n";
            return;
        }
    }
    if ( nombre.empty() || ruta.empty()){
        printf("ERROR: parametros necesarios inexistentes\n");
        return;
    }
    mbr * mbr = montar ( ruta );
    int res;
    bool part = buscarpart(mbr, nombre);
    if (!part){
        int extra = -1;
        for (int i = 0; i < 4; i++){
            if ( mbr ->mbr_partition[i].part_type == 'e'){
                extra =  i;
                break;
            }
        }
        std::cout << "estamos buscando logica\n";
        res = buscarlogica(extra, ruta, mbr, nombre);
        if (res == -1){
            std::cout << "no existe la particion\n";
            return; 
        }
        montarpart(ruta, nombre);
    }else{
        //montar la particion especificada
        montarpart( ruta , nombre);
    }
    

}

void montarpart(std::string path, std::string nombre){
    std::string boot = "boot.dk";
    lmo *lista = new lmo;
    FILE *arch;
    arch= fopen(boot.c_str(), "rb+");
    if (arch == NULL)
    {
        arch = fopen(boot.c_str(), "wb+");
        fwrite(lista, sizeof(lmo), 1, arch);
    }
    fseek(arch, 0, SEEK_SET);
    fread(lista,sizeof(lmo), 1, arch);
    char letra = 96;
    int activas = 0;
    bool bandera = false;
    std::string lias="vd";
    std::string dis ;
    std::string name ;
    std::string alita;
    for(int i = 0; i < 40; i++){
        dis = lista->lista[i].disco;
        name = lista->lista[i].nombre;
        alita = lista->lista[i].alias;
        if (dis == path){
            std::cout << "ya existe el disco\n";
            if (name == nombre){
                std::cout << "ya esta montada\n";
                fclose(arch);
                return;
            }
            bandera = true;
            letra = lista->lista[i].alias[2];
            std::string iox = lista->lista[i].alias;
            iox.erase(0, 3);
            if( activas < stoi(iox)){
                activas = stoi(iox);
            }
        }else {
            std::cout << "no hay vacias y no es el mismo disco "<< letra <<"\n";
            if (alita != "" && alita[0] == 'v' && alita[1] == 'd'){
                if(letra < (alita[2])){
                    letra = alita[2];
                }
            }
        }

    }
    for(int i = 0; i < 40; i++){
        dis = lista->lista[i].disco;
        name = lista->lista[i].nombre;
        alita = lista->lista[i].alias;
        if (dis.empty()){
            std::cout << "asignando nueva\n";
            activas++;
            if ( !bandera ) {letra += 1;}
            strcpy(lista->lista[i].disco, path.c_str());
            strcpy(lista->lista[i].nombre, nombre.c_str());
            lias = "vd" ;
            lias+= letra ;
            lias+= std::to_string(activas);
            strcpy(lista->lista[i].alias,lias.c_str());
            std::cout << path << "-" << nombre <<"-"<< lista->lista[i].alias<<"\n";
            break;
        }
    }
    std::cout << "llego al final del metodo\n";
    //std::sort(lista->lista, lista->lista + 30, order);
    fseek(arch, 0, SEEK_SET);
    fwrite(lista, sizeof(lmo), 1, arch);
    fclose(arch);

}

void desmontar ( int num, char**command){
    std::string para;
    std::string nombre="";
    std::string token;
    std::string delimiter = "~:~";

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
        if (token == "-id"){
            nombre = para;
        }else {
            std::cout << "ERROR: parametro no permitido\n";
            return;
        }
    }
    if ( nombre.empty()){
        printf("ERROR: parametros necesarios inexistentes\n");
        return;
    }

    std::string boot = "boot.dk";
    lmo *lista = new lmo;
    FILE *arch;
    arch= fopen(boot.c_str(), "rb+");
    if (arch == NULL)
    {
        std::cout << "error no existe ninguna particion montada\n";
        return;
    }
    fseek(arch, 0, SEEK_SET);
    fread(lista,sizeof(lmo), 1, arch);
    for(int i = 0; i < 40; i++){
        std::string alias = lista->lista[i].alias;
        if ( alias == nombre){
            strcpy(lista->lista[i].alias,"");
            strcpy(lista->lista[i].nombre,"");
            strcpy(lista->lista[i].disco,"");
        }
    }
    
    //std::sort(lista.lista, lista.lista + 30, order);
    /*for(int i = 0; i < 40; i++){
        for(int j = 0; j <(40-i); j++){
            if(lista->lista[j].disco < lista->lista[j+1].disco){
                modisk aux = lista->lista[j];
                lista -> lista[j] = lista -> lista[j+1];
                lista -> lista[j+1] = aux;
            }
        }
    }*/
    for(int i = 0; i < 40; i++){
        std::string rasa ( lista->lista[i].alias);
        if ( !rasa.empty()){
            std::cout << lista->lista[i].alias << "\n";
            std::cout << lista->lista[i].nombre << "\n";
            std::cout << lista->lista[i].disco << "\n";
        }
        
    }
    fseek(arch, 0, SEEK_SET);
    fwrite(lista, sizeof(lmo), 1, arch);
    fclose(arch);
    std::cout << "unidad desmontada\n";
}



mbr * montar ( std::string path){
    //escritura en disco del mbr
    mbr * diskmbr;
    FILE *arch;
    arch= fopen(path.c_str(), "rb");
    if (arch == NULL)
        exit(1);
    fseek(arch, 0, SEEK_SET);
    fread(diskmbr, sizeof(mbr), 1, arch);
    fclose(arch);
    return diskmbr;
}

int buscarpart (mbr * mbr, std::string nombre ){
    for (int i = 0; i < 4; i++){
        if ( mbr ->mbr_partition[i].part_name == nombre){
            //aqui debo aumentar el conteo de mount del superbloque
            return true;
        }
    }
    return false;
}

int buscarlogica (int pos, std::string path, mbr * mbr, std::string nombre){
    partition logica = mbr->mbr_partition[pos];
    int startlogic = mbr->mbr_partition[pos].part_start;
    if (logica.part_next == -1){
        return -1;
    }
    FILE *arch;
    arch= fopen(path.c_str(), "rb+");
    fseek(arch, startlogic, SEEK_SET);
    fread(&logica, sizeof(partition), 1, arch);
    do{
        if(logica.part_name == nombre){
            //aqui modifico el superbloqe
            fclose(arch);
            return 1;
        }else{
            //std::cout << "part logica actual\n";
            //displaypart(logica);
            startlogic = logica.part_next;
            fseek(arch, logica.part_next, SEEK_SET);
            fread(&logica, sizeof(partition), 1, arch);
        }
    }while ( startlogic != -1 );
    fclose(arch);
    return -1;
}
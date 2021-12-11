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


void part_montar (char** command, int num){
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
            }
        }
        res = buscarlogica(mbr ->mbr_partition[extra].part_start, ruta, mbr, nombre);
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
    lmo lista;
    FILE *arch;
    arch= fopen(boot.c_str(), "rb+");
    if (arch == NULL)
    {
        fclose(arch);
        arch = fopen(boot.c_str(), "wb+");
        fwrite(&lista, sizeof(lmo), 1, arch);
    }
    fseek(arch, 0, SEEK_SET);
    fread(&lista,sizeof(lmo), 1, arch);
    std::string prefix = "vd";
    char letra = 97;
    int activas = 0;
    for(int i = 0; i < 30; i++){
        if (lista.lista[i].disco == "-"){
            activas++;
            lista.lista[i].disco = path;
            lista.lista[i].nombre = nombre;
            lista.lista[i].alias = prefix + letra + std::to_string(activas);
            std::cout << path << "-" << nombre <<"-"<<lista.lista[i].alias<<"\n";
            break;
        }else if (lista.lista[i].disco == path){
            if (lista.lista[i].nombre == nombre){
                std::cout << "ya esta montada\n";
                fclose(arch);
                return;
            }
            letra = lista.lista[i].alias[2];
            std::string iox = lista.lista[i].alias;
            iox.erase(0, 3);
            if( activas < stoi(iox)){
                activas = stoi(iox);
            }
        }else {
            if(letra < lista.lista[i].alias[2]){
                letra = lista.lista[i].alias[2];
            }
        }

    }
    
    //std::sort(lista.lista, lista.lista + 30, modisk::order);
    fseek(arch, 0, SEEK_SET);
    fwrite(&lista, sizeof(lmo), 1, arch);
    fclose(arch);

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
    return diskmbr;
}

int buscarpart (mbr * mbr, std::string nombre ){
    for (int i = 0; i < 4; i++){
        if ( mbr ->mbr_partition[i].part_name == nombre){
            return true;
        }
    }
    return false;
}

int buscarlogica (int pos, std::string path, mbr * mbr, std::string nombre){
    partition logica;
    int startlogic = pos;
    FILE *arch;
    arch= fopen(path.c_str(), "rb+");
    fseek(arch, pos, SEEK_SET);
    fread(&logica, sizeof(partition), 1, arch);
    do{
        if(logica.part_name == nombre){
            return 1;
        }else{
            //std::cout << "part logica actual\n";
            //displaypart(logica);
            startlogic = logica.part_next;
            fseek(arch, logica.part_next, SEEK_SET);
            fread(&logica, sizeof(partition), 1, arch);
        }
    }while ( startlogic != -1 );
    return -1;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
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
    mk -> borrar = "";
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

    obtenerMBR ( mk );
    
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
    if ( mk -> agregar && mk->borrar.empty()){//parte para agregar
        bool p_existe = false;
        bool p_ext_existe = false;
        int p_posicion;
        for( int i = 0; i < 4; i++){
            if(disk -> mbr_partition[i].part_name == mk ->name){
                p_existe = true;
                p_posicion = i;
                break;
            }
        }
        if ( p_existe){

        }


    } else if ( !mk -> agregar && !mk->borrar.empty()){//parte para borrar

    }else{
        printf("comando add o delete no reconocido\n");
    }

}
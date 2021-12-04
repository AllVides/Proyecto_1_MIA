#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../include/myUtil.h"
#include "../include/disco.h"

void Disco::makedisk (char ** command, int num)
{
    MKDISK_PARAM * mk = (MKDISK_PARAM *)malloc(sizeof(MKDISK_PARAM));
    mk -> size = 0;
    mk -> f = "FF";
    mk -> u = "M";

    std::string para;
    std::string aux;
    std::string token;
    std::string delimiter = "~:~";

    //este for es modelo de como se lleva a cabo el reconocimiento de opciones del comando
    for (int i = 2; i < num; i++){
        size_t pos = 0;
        para = std::string(MyUtil::aMayus(command[i]));
        pos = para.find(delimiter);
        token = para.substr(0, pos);
        para.erase(0, pos + delimiter.length());

        if (token == "-PATH"){
            mk -> path = para;

        }else if (token == "-SIZE"){
            mk -> size = stoi(para);

        }else if (token == "-U"){
            if(para != "K" && para != "M"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< aux << "\n";
                return;
            }
            mk -> u = para;

        }else if (token == "-F"){
            if(aux != "BF" && aux != "FF" && aux != "WF"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< aux << "\n";
                return;
            }
            mk -> f= para;

        }
    
    }
    //se verifican los obligatorios
    if(mk -> size == 0 || mk -> path.empty()){
        printf("ERROR: parametros necesarios inexistentes");
        return;
    }

    createDir (mk);
    createFile(mk);
    
}

void Disco::createDir (MKDISK_PARAM *mk)
{
    std::string s = mk -> path;
    std::string delimiter = "/";

    size_t i = 0;
    std::string token;
    std::string dir = "";
    while ((i = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, i);
        dir += "/"+token;
        s.erase(0, i + delimiter.length());
    }
    std::string camino = "mkdir -p " + dir;
    system(camino.c_str());
}

void Disco::createFile (MKDISK_PARAM *mk)
{
    //mbr mbrdisk;
    FILE *arch;
    arch= fopen(mk->path.c_str(), "wb");

    if (arch == NULL)
        exit(1);
    char buffer[1024];
    for(int i = 0 ; i < 1024 ; i++){
            buffer[i] = '\0';
        }
    if (mk->u == "K"){
        //descripcion del disco mbr
        for(int i = 0; i < (mk->size); i++){
            fwrite(&buffer, 1024, 1, arch);
        }
        fclose(arch);
    }
    else if (mk->u == "M"){
        //descripcion del disco mbr
        for(int i = 0; i < (mk->size*1024); i++){
            fwrite(&buffer, 1024, 1, arch);
        }
        fclose(arch);
    }

}

void Disco::removedisk (char** path, int num)
{
    return;
}
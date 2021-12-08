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
    mk -> f = "ff";
    mk -> u = "m";

    std::string para;
    std::string aux;
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
            if(para != "k" && para != "m"){ 
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

        }else{
            printf("tipo de parametro desconocido");
        }
    
    }
    //se verifican los obligatorios
    if(mk -> size == 0 && mk -> path.empty()){
        printf("ERROR: parametros necesarios inexistentes\n");
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
    //creacion de informacion del mbr
    mbr *mbrdisk = (mbr *)malloc(sizeof(mbr));
    mbrdisk->mbr_disk_signature = (rand()%100);
    mbrdisk->disk_fit = mk->f[0];
    mbrdisk->hora = time(0);
    //inicio escritura del archivo
    FILE *arch;
    arch= fopen(mk->path.c_str(), "wb");

    if (arch == NULL)
    {
        printf("archivo inexistente, y llegaste a un lugar raro");
        exit(1);
    }
    char buffer[1024];
    for(int i = 0 ; i < 1024 ; i++){
            buffer[i] = '\0';
    }
    if (mk->u == "k"){
        //descripcion del disco mbr
        mbrdisk -> size = mk ->size * 1024;
        for(int i = 0; i < (mk->size); i++){
            fwrite(buffer, 1024, 1, arch);
        }
        fclose(arch);
    }
    else if (mk->u == "m"){
        //descripcion del disco mbr
        mbrdisk -> size = mk ->size * 1024 * 1024;
        for(int i = 0; i < (mk->size*1024); i++){
            fwrite(buffer, 1024, 1, arch);
        }
        fclose(arch);
    }
    
    partition particionVacia;
    particionVacia.part_status = 0;
    particionVacia.part_type = '-';
    particionVacia.part_fit = '-';
    particionVacia.part_start = 0;
    particionVacia.part_size = 0;
    strcpy(particionVacia.part_name ,"ja");

    for( int i = 0; i < 4; i++){
        mbrdisk -> mbr_partition[i] = particionVacia;
    }
    
    //escritura en disco del mbr
    arch= fopen(mk->path.c_str(), "rb+");

    if(arch !=NULL){
        fseek(arch,0,SEEK_SET);
        fwrite(mbrdisk, sizeof(mbr), 1,arch);
        fclose(arch);
        displaymbr(mbrdisk);
        printf("disco creado xdxdxd \n");
    }else{
        printf("ERROR: No se puede generar el disoc\n");
    }
    printf("proceso terminado\n");

}

void Disco::removedisk (char** command, int num)
{
    std::string para;
    std::string aux;
    std::string token;
    std::string delimiter = "~:~";

    for (int i = 2; i < num; i++){
        size_t pos = 0;
        para = std::string(MyUtil::aLower(command[i]));
        pos = para.find(delimiter);
        token = para.substr(0, pos);
        para.erase(0, pos + delimiter.length());

        if (token == "-path"){
            aux = para;
        } else {
            std::cout << "ERROR: parametro no permitido\n";
            return;
        }
    }
    std::string filerem = "rm -i " + para;
    system(filerem.c_str());
    printf("disco eliminado exitosamente\n");
    
}

void escribirmbr (mbr *mbrdisk , std::string path){
    //escritura en disco del mbr
    FILE *arch;
    arch= fopen(path.c_str(), "rb+");

    if(arch !=NULL){
        fseek(arch,0,SEEK_SET);
        fwrite(mbrdisk, sizeof(mbr), 1,arch);
        fclose(arch);
        displaymbr(mbrdisk);
        printf("mbr escrito xdxdxd \n");
    }else{
        printf("ERROR: No se puede generar el disoc\n");
    }
    printf("proceso terminado\n");
}

void displaymbr (mbr *cosa){
    std::cout << sizeof(mbr)<<"\n";
    std::cout<< cosa->disk_fit<<"\n";
    std::cout<< asctime(localtime(&cosa->hora));
    std::cout<< cosa->mbr_disk_signature<<"\n";
    std::cout<< cosa->size<<"\n";
    for( int i = 0; i < 4; i++){
        displaypart(cosa -> mbr_partition[i]);
    }
    
}

void displaypart (partition part)
{
    std::cout << part.part_status <<"\n";
    std::cout <<part.part_type <<"\n";
    std::cout <<part.part_fit <<"\n";
    std::cout <<part.part_start <<"\n";
    std::cout <<part.part_size <<"\n";
    std::cout <<part.part_name <<"\n";
}
#ifndef __FORMATO_H__
#define __FORMATO_H__
#include <string>
#include <iostream>
#include "./disco.h"

typedef struct espaciodis {
    int inicio;
    int size;
}espaciodis;

void freespace (mbr * disk, espaciodis blancos[]);

class Formato{
    public:
    typedef struct FDISK_PARAM {
        std::string path;
        int size;
        std::string f;
        std::string u;
        std::string type;
        std::string borrar;
        int agregar;
        std::string name;


        /* Otros commandos a implementar */
    } FDISK_PARAM;

    void formatdisk (char ** command, int num);
    mbr* obtenerMBR (FDISK_PARAM *mk);
    void definepart (mbr * disk, FDISK_PARAM* mk);

    //void createFile (MKDISK_PARAM *mk);

};

#endif
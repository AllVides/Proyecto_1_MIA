#ifndef __FORMATO_H__
#define __FORMATO_H__
#include <string>
#include <iostream>
#include "./disco.h"


class Formato{
    public:
    typedef struct FDISK_PARAM {
        std::string path;
        int size;
        std::string f;
        std::string u;
        std::string type;
        bool borrar;
        bool agregar;
        std::string name;


        /* Otros commandos a implementar */
    } FDISK_PARAM;

    void formatdisk (char ** command, int num);
    void obtenerMBR (FDISK_PARAM *mk);
    //void createFile (MKDISK_PARAM *mk);

};

#endif
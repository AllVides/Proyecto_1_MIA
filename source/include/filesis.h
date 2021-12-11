#ifndef __FILESIS_H__
#define __FILESIS_H__
#include <string>
#include <iostream>
#include "./disco.h"
#include "./formato.h"
#include "./mount.h"

class Filesis{
    public:
    typedef struct MKFS_PARAM {
        std::string path;
        int size;
        std::string f;
        std::string u;
        std::string type;
        std::string borrar;
        int agregar;
        std::string name;
        /* Otros commandos a implementar */
    } MKFS_PARAM;

    void makefs (char ** command, int num);
    //mbr* obtenerMBR (FDISK_PARAM *mk);
    
    

    //void createFile (MKDISK_PARAM *mk);

};

#endif
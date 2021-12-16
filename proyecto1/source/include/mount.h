#ifndef __MOUNT_H__
#define __MOUNT_H__
#include <string>
#include <iostream>
#include "./disco.h"
#include "./formato.h"



typedef struct modisk {
    char disco[100] ;
    char nombre[16];
    char alias[8];
    
}modisk;

typedef struct lmo {
    modisk lista[40];
    
}lmo;
static bool order(const modisk& a,const modisk& b) { return a.disco > b.disco; }
void part_montar ( int num,char** command);
mbr *  montar ( std::string path);
int buscarpart (mbr * mbr, std::string nombre);
int buscarlogica (int pos, std::string path, mbr * mbr, std::string nombre);
void montarpart (std::string path, std::string nombre);
void desmontar ( int num, char**command);




#endif
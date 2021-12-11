#ifndef __MOUNT_H__
#define __MOUNT_H__
#include <string>
#include <iostream>
#include "./disco.h"
#include "./formato.h"



typedef struct modisk {
    std::string disco = "-";
    std::string nombre = "-";
    std::string alias = "-";
    static bool order(const modisk& a,const modisk& b) { return a.disco > b.disco; }
}modisk;

typedef struct lmo {
    modisk lista[30];
}lmo;

void part_montar (char** command, int num);
mbr *  montar ( std::string path);
int buscarpart (mbr * mbr, std::string nombre);
int buscarlogica (int pos, std::string path, mbr * mbr, std::string nombre);
void montarpart (std::string path, std::string nombre);



#endif
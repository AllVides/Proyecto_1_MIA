#ifndef __REP_H__
#define __REP_H__

#include <iostream>

typedef struct REP_PARAM {
        std::string id;
        std::string name;
        std::string path;
        std::string ruta;

        /* Otros commandos a implementar */
    } REP_PARAM;

void rep_disk();
void rep_mbr();
void rep_sb();
void rep_bmi();
void rep_bmb();


#endif
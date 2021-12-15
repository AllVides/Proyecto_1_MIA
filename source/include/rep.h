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

void reporte(int num, char ** command);
void rep_disk(REP_PARAM *mk);
void rep_mbr(REP_PARAM *mk);
void rep_sb(REP_PARAM *mk);
void rep_bmi(REP_PARAM *mk);
void rep_bmb(REP_PARAM *mk);

///utilidades
void createdir(REP_PARAM *mk);
void createfile(REP_PARAM *mk, std::string contenido);


#endif
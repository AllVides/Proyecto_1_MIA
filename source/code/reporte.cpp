#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <cmath>
#include "../include/myUtil.h"
#include "../include/disco.h"
#include "../include/formato.h"
#include "../include/mount.h"
#include "../include/filesis.h"
#include "../include/rep.h"

void reporte(int num, char ** command){
    REP_PARAM *mk = (REP_PARAM *)malloc(sizeof(REP_PARAM));
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
        int posi = 0;
               while ((posi = para.find(' ')) != std::string::npos) {
                    para.replace(posi, 1, "_");
               }
        if (token == "-path"){
            mk -> path = para;

        }else if (token == "-id"){ //pendiente de modificar
            mk -> id = para;

        }else if (token == "-ruta"){//pendiente de modificar
            mk -> ruta= para;


        }else if (token == "-name"){//pendiente de modificar
            mk -> name= para;

        }else if (para[0] == '#' || para[0] == '/'){
            std::cout<<"\033[92m" <<para << "\033[0m\n";
            break;

        }else{
            printf("tipo de parametro desconocido\n");
            return;
        }
    
    }

    if(mk -> id.empty() || mk -> name.empty() || mk -> path.empty() ){
        printf("ERROR: parametros necesarios inexistentes\n");
        return;
    }

    //dot -Kdot -Tpng sample.dot  -o sample.png 
    if (mk->name == "mbr"){

    }else if (mk->name == "disk"){
        
    }else if (mk->name == "inode"){
        std::cout <<"proximamente\n";
    }else if (mk->name == "journaling"){
        std::cout <<"proximamente\n";
    }else if (mk->name == "block"){
        std::cout <<"proximamente\n";
    }else if (mk->name == "bm_inode"){
        
    }else if (mk->name == "bm_block"){
        
    }else if (mk->name == "tree"){
        std::cout <<"proximamente\n";
    }else if (mk->name == "sb"){
        
    }else if (mk->name == "file"){
        std::cout <<"proximamente\n";
    }else if (mk->name == "ls"){
        std::cout <<"proximamente\n";
    }else{
        std::cout <<"comando no encontrado\n";
        return;
    }
}
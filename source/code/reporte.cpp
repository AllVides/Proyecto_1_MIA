#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <algorithm>
#include <cmath>
#include <iostream>
#include <fstream>
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
        rep_mbr(mk);
        std::cout << "reporte de mbr creado\n";
    }else if (mk->name == "disk"){
        rep_disk(mk);
        std::cout << "reporte de disk creado\n";
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


///////////reporte de mbr ////////////////////////////////

void rep_mbr(REP_PARAM *mk){
    std::string encabezado = "digraph G {\n";
        encabezado +="rankdir=\"TB\";\n";
        encabezado +="node [shape=box];\n";
        encabezado +="nodo0[shape= plaintext\n";
        encabezado +="label=<<table border =\"1\" cellspacing=\"0\">\n";

    

    modisk ruta = getruta(mk -> id);
    std::cout << "obtuvimos modisk\n"<< ruta.disco << "\n";
    mbr * cosa=montar(ruta.disco);
    std::cout << "obtuvimos el mbr\n";


    std::string cuerpo = "<tr><td> fit </td><td>";
    cuerpo += cosa->disk_fit;
    cuerpo += "</td></tr>\n";

    cuerpo += "<tr><td> hora de creacion </td><td>" ;
    cuerpo += asctime(localtime(&cosa->hora));
    cuerpo += "</td></tr>\n";

    cuerpo += "<tr><td> disk_signature </td><td>" ;
    cuerpo += std::to_string(cosa->mbr_disk_signature);
    cuerpo += "</td></tr>\n";

    cuerpo += "<tr><td> disk_size </td><td>" ;
    cuerpo+= std::to_string(cosa->size);
    cuerpo += "</td></tr>\n";

    for( int i = 0; i < 4; i++){
        partition part = cosa -> mbr_partition[i];
        cuerpo += "<tr><td ROWSPAN= \"2\">Particion"+std::to_string(i);
        cuerpo+="</td></tr>\n";

        cuerpo += "<tr><td> part_status </td><td>" ;
        cuerpo+= std::to_string(part.part_status);
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_type </td><td>" ;
        cuerpo+= part.part_type;
        cuerpo += "</td></tr>\n";
        
        cuerpo += "<tr><td> part_name </td><td>" ;
        cuerpo+= part.part_name;
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_fit </td><td>" ;
        cuerpo+= part.part_fit;
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_start </td><td>" ;
        cuerpo+= std::to_string(part.part_start);
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_size </td><td>" ;
        cuerpo+= std::to_string(part.part_size);
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_next </td><td>" ;
        cuerpo+= std::to_string(part.part_next);
        cuerpo += "</td></tr>\n";

        /*std::cout << part.part_status <<"\n";
        //std::cout <<part.part_type <<"\n";
        //std::cout <<part.part_fit <<"\n";
        //std::cout <<part.part_start <<"\n";
        //std::cout <<part.part_next <<"\n";
        //std::cout <<part.part_size <<"\n";
        //std::cout <<part.part_name <<"\n";*/
    }
    cuerpo += "</table>>]";

    bool existe = false;
    partition algo;
    for( int i = 0; i < 4; i++){
        if(cosa->mbr_partition[i].part_type == 'e'){
            algo = cosa->mbr_partition[i];
            if (algo.part_next != -1){
                existe = true;
            }
            
            break;
        }
    }
    if (existe){
        int startlogic = algo.part_start;
        FILE *arch;
        std::string path = ruta.disco;
        arch= fopen(path.c_str(), "rb");
        fseek(arch, startlogic, SEEK_SET);
        fread(&algo, sizeof(partition), 1, arch);
        int i = 0;
        do{

        cuerpo+= "nodo"+std::to_string(i+1);
        cuerpo+= "[shape= plaintext label=<<table border =\"1\" cellspacing=\"0\">";

        cuerpo += "<tr><td ROWSPAN= \"2\">Logica"+std::to_string(i);
        cuerpo+="</td></tr>\n";

        cuerpo += "<tr><td> part_status </td><td>" ;
        cuerpo+= std::to_string(algo.part_status);
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_type </td><td>" ;
        cuerpo+= algo.part_type;
        cuerpo += "</td></tr>\n";
        
        cuerpo += "<tr><td> part_name </td><td>" ;
        cuerpo+= algo.part_name;
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_fit </td><td>" ;
        cuerpo+= algo.part_fit;
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_start </td><td>" ;
        cuerpo+= std::to_string(algo.part_start);
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_size </td><td>" ;
        cuerpo+= std::to_string(algo.part_size);
        cuerpo += "</td></tr>\n";

        cuerpo += "<tr><td> part_next </td><td>" ;
        cuerpo+= std::to_string(algo.part_next);
        cuerpo += "</td></tr>\n";
        cuerpo += "</table>>]";

        i++;
        startlogic = algo.part_next;
        fseek(arch, algo.part_next, SEEK_SET);
        fread(&algo, sizeof(partition), 1, arch);
        
        }while ( startlogic != -1 );
        fclose(arch);
    }

    cuerpo += "}";
    encabezado += cuerpo;
    createfile(mk, encabezado);
    std::cout << "reporte mbr creado\n";

}

//////////reporte disk///////////////////////////////////
void rep_disk(REP_PARAM *mk){
    modisk ruta = getruta(mk -> id);
    std::cout << "obtuvimos modisk\n"<< ruta.disco << "\n";
    mbr * cosa=montar(ruta.disco);
    std::cout << "obtuvimos el mbr\n";
    int tamanio = cosa -> size;
    
    std::string encabezado = "digraph G {\n";
        encabezado +="rankdir=\"TB\";\n";
        encabezado +="node [shape=box];\n";
        encabezado +="nodo0[ shape= plaintext\n";
        encabezado +="label=<<table border =\"1\" cellspacing=\"0\" cellpadding= \"4\"><tr>";

    std::string cuerpo = "";
    for( int i = 0; i < 4; i++){
        partition part = cosa -> mbr_partition[i];
        if( part.part_type == 'p'){
            cuerpo+="<td ROWSPAN=\"2\">";
            cuerpo+= part.part_name;
            cuerpo += "<br/>";

            cuerpo += "inicio: " ;
            cuerpo+= std::to_string(part.part_start);
            cuerpo += "<br/>";

            cuerpo += "size: " ;
            cuerpo+= std::to_string(part.part_size);
            cuerpo += "<br/>";
            
        }else {
             cuerpo+="<td COLSPAN=\"2\">";
            cuerpo+=  part.part_name;
             cuerpo+="<hr>";
            
            partition algo = part;
            bool existe = false;
            if (algo.part_next != -1){
                existe = true;
            }
            if(existe){
            int startlogic = algo.part_start;
            FILE *arch;
            std::string path = ruta.disco;
            arch= fopen(path.c_str(), "rb");
            fseek(arch, startlogic, SEEK_SET);
            fread(&algo, sizeof(partition), 1, arch);
            do{
               
                cuerpo+= algo.part_name;
                cuerpo += "<br/>";
                cuerpo += "inicio: " ;
                cuerpo+= std::to_string(algo.part_start);
                cuerpo += "<br/>";
                cuerpo += "size: " ;
                cuerpo+= std::to_string(algo.part_size);
                cuerpo += "<br/>";
                startlogic = algo.part_next;
                fseek(arch, algo.part_next, SEEK_SET);
                fread(&algo, sizeof(partition), 1, arch);
        
            }while ( startlogic != -1 );
            fclose(arch);
            }
            cuerpo += " } } ";
        }
        cuerpo += "</td>";
        

    }
    cuerpo += "libre";
    cuerpo += "\"];";
    encabezado += cuerpo;
    createfile(mk, encabezado);
    std::cout << "reporte mbr creado\n";
}




void createdir (REP_PARAM *mk)
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

void createfile(REP_PARAM *mk, std::string contenido){
    createdir (mk);
    std::string ruta = mk->path + ".dot";
    std::ofstream file;
    file.open(ruta.c_str());
    file << contenido;
    file.close();
    std::string eje = "sudo dot -Tpng " + ruta + " -o " + mk->path; 
    system(eje.c_str());
    std::cout << "reporte creado\n";
}
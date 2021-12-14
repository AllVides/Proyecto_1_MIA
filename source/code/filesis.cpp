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


void makefs (int num, char ** command){
    MKFS_PARAM * mk = (MKFS_PARAM *)malloc(sizeof(MKFS_PARAM));
    mk -> type = "full";
    mk ->fs = "2fs";

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
        if (token == "-id"){
            
            mk -> id = para;

        }else if (token == "-type"){
            if(para != "fast" && para != "full"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< para << "\n";
                return;
            }
            mk -> type = para;

        }else if (token == "-fs"){
            if(para != "2fs" && para != "3fs"){ 
                std::cout << "ERROR: valor de parametro erroneo -> "<< para << "\n";
                return;
            }
            mk -> fs= para;

        }else if (para[0] == '#' || para[0] == '/'){
            std::cout<<"\033[92m" <<para << "\033[0m\n";
            break;

        }else{
            printf("tipo de parametro desconocido\n");
            return;
        }
    
    }
    //se verifican los obligatorios
    if(mk -> id.empty() ){
        printf("ERROR: parametros necesarios inexistentes\n");
        return;
    }
    std::cout << "empezo mkfs\n";
    modisk ruta = getruta(mk -> id);
    std::cout << "obtuvimos modisk\n"<< ruta.disco << "\n";
    mbr * mbr=montar(ruta.disco);
    std::cout << "obtuvimos el mbr\n";
    buildfs(ruta, mbr);
    std::cout << "termino mkfs\n";
    exit(0);

}

void buildfs (modisk ruta, mbr * disk)
{
    std::cout << "iniciamos buildfs "  << "\n";
    sblock* superb = new sblock();
    std::cout << "creamos superbloque "  << "\n";
    std::string r = ruta.disco;
    std::string t = ruta.nombre;
    std::cout << "se recupera una particion "  << "\n";
    partition f = getparticion (disk, t, r);
    displaypart(f);
    int nin = floor((f.part_size -sizeof(sblock))/(1+3+sizeof(inode)+3*(64)));
    std::cout << "calculo el espacio " << nin << "\n";
    int inicio = f.part_start;
    char bmin[nin];
    char bmbl[3*nin];
     std::cout << "declaro los bitmaps " << sizeof(bmin) << "\n";
    for(int i = 0; i<nin; i++){
        bmin[i]='0';
    }
    for(int i = 0; i<3*nin; i++){
        bmbl[i]='0';
    }
    std::cout << "creo el superbloque " << "\n";
    superb->s_fs_type = 2;//2 o 3
    superb->s_in_count=nin;//numero de inodos
    superb->s_ib_count=nin*3;//numero de bloques
    superb->s_fb_count=nin*3;//numero de bloques vacios
    superb-> s_fi_count=nin;//numero de nodos vacios
    superb-> s_mtime =time(0);;//fecha ultimo montaje
    superb->s_umtiem =time(0);;//fecha de unmount
    superb->s_mnt_cout =1;//conteo de mount
    superb->s_magic = 0xEF53;//numero magico
    superb->s_in_size = sizeof(inode);//tama;o del inodo
    superb->s_ib_size = 64;//tama;io del bloque
    superb->s_first_in=0;//primer inodo libre
    superb->s_first_ib=0;//primer bloque libre
    superb->s_bm_inode_s= inicio + sizeof(sblock);//inicio del bitmap de inodos
    superb->s_bm_iblock_s=inicio + sizeof(sblock)+nin;//inicio del bitmap de bloques
    superb->s_in_start=inicio + sizeof(sblock)+nin+3*nin;//inicio de inodos
    superb->s_ib_start=inicio + sizeof(sblock)+nin+3*nin+nin*sizeof(inode);//inicio de bloques

    FILE *arch;
    std::cout << "abro el archivo " << r << "\n";
    arch= fopen(r.c_str(), "rb+");
    fseek(arch, f.part_start, SEEK_SET);
    //fread(&f, sizeof(partition), 1, arch);
    std::cout <<fwrite(superb, sizeof(sblock), 1, arch);
    std::cout <<fwrite(bmin, sizeof(bmin),1, arch);
    std::cout <<fwrite(bmbl, sizeof(bmbl),1, arch);
    fclose(arch);
    
    std::cout<<"file system created\n";

}


partition getparticion (mbr * disk, std::string nombre, std::string path){
    partition  part;
    //obtenemos posicion de la posicion de la particion
    for(int i = 0; i < 4 ; i++){
        if(disk->mbr_partition[i].part_name == nombre){
            part = disk->mbr_partition[i];
            return part;
        }
    }
    bool existe = false;
    for(int i = 0; i < 4 ; i++){
        if(disk->mbr_partition[i].part_type == 'e'){
            part = disk->mbr_partition[i];
            existe = true;
            break;
        }
    }
    int startlogic = part.part_start;
    FILE *arch;
    arch= fopen(path.c_str(), "rb+");
    fseek(arch, startlogic, SEEK_SET);
    fread(&part, sizeof(partition), 1, arch);
    do{
        if(part.part_name == nombre){
            //aqui modifico el superbloqe
            
            break;
        }else{
            startlogic = part.part_next;
            fseek(arch, part.part_next, SEEK_SET);
            fread(&part, sizeof(partition), 1, arch);
        }
    }while ( startlogic != -1 );
    fclose(arch);
    displaypart(part);
    return part;
}

modisk getruta (std::string id)
{
    std::string boot = "boot.dk";
    modisk ruta;
    lmo *lista = new lmo;
    FILE *arch;
    arch= fopen(boot.c_str(), "rb");
    if (arch == NULL)
    {
        std::cout << "error no existe ninguna particion montada\n";
        return ruta;
    }
    fseek(arch, 0, SEEK_SET);
    fread(lista,sizeof(lmo), 1, arch);
    for(int i = 0; i < 40; i++){
        std::string alias = lista->lista[i].alias;
        if ( alias == id){
            ruta = lista->lista[i];
            break;
        }
    }
    fclose(arch);
    
    return ruta;
}
#ifndef __FILESIS_H__
#define __FILESIS_H__
#include <string>
#include <iostream>
#include "./disco.h"
#include "./formato.h"
#include "./mount.h"

typedef struct sblock {
        int s_fs_type = 2;//2 o 3
        int s_in_count;//numero de inodos
        int s_ib_count;//numero de bloques
        int s_fb_count;//numero de bloques vacios
        int s_fi_count;//numero de nodos vacios
        time_t s_mtime =time(0);;//fecha ultimo montaje
        time_t s_umtiem =time(0);;//fecha de unmount
        int s_mnt_cout =1;//conteo de mount
        int s_magic = 0xEF53;//numero magico
        int s_in_size;//tama;o del inodo
        int s_ib_size = 64;//tama;io del bloque
        int s_first_in=0;//primer inodo libre
        int s_first_ib=0;//primer bloque libre
        int s_bm_inode_s;//inicio del bitmap de inodos
        int s_bm_iblock_s;//inicio del bitmap de bloques
        int s_in_start;//inicio de inodos
        int s_ib_start;//inicio de bloques
        /* Otros commandos a implementar */
    } sblock;

typedef struct inode{
        int i_uid;
        int i_gid;
        int i_size;
        time_t i_atime;
        time_t i_ctime;
        time_t i_mtime;
        int iblock[15];
        char i_type;
        int i_perm;
    }inode;

typedef struct bcont{
        char b_name[12];
        int b_inodo;
    }bcont;

typedef struct carpblock{
        bcont b_cont[4];
    }carpblock;

typedef struct fileblock{
        char b_cont[64];
    }fileblock;

typedef struct pointblock{
        int pointers[16];
    }pointblock;


typedef struct MKFS_PARAM {
        std::string id;
        std::string type;
        std::string fs;
        /* Otros commandos a implementar */
    } MKFS_PARAM;



void makefs ( int num, char ** command);
modisk getruta ( std::string id);
void buildfs (modisk ruta, mbr * disk);
partition getparticion (mbr*disk, std::string nombre, std::string path);

    //mbr* obtenerMBR (FDISK_PARAM *mk);
    
    

    //void createFile (MKDISK_PARAM *mk);

#endif
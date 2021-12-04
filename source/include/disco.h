#ifndef __CREARDISCO_H__
#define __CREARDISCO_H__
#include <string>
#include <iostream>

typedef struct mbr {
        int size;
        time_t hora;
        int mbr_disk_signature;
        //char* disk_fit;
        //partition mbr_partition_1;
        //partition mbr_partition_2;
        //partition mbr_partition_3;
        //partition mbr_partition_4;

        /* Otros commandos a implementar */
    } mbr;

typedef struct partition {
        char part_status;
        char part_type;
        char part_fit;
        int part_start;
        int part_size;
        int part_name;
    } partition;

class Disco{
    public:
    typedef struct tagCOMMAND {
        std::string path;
        int size;
        std::string f;
        std::string u;

        /* Otros commandos a implementar */
    } MKDISK_PARAM;

    void makedisk (char ** command, int num);
    void createDir (MKDISK_PARAM *mk);
    void createFile (MKDISK_PARAM *mk);
    void removedisk (char ** command, int num);

};

#endif
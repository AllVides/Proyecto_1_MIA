#ifndef __DISCO_H__
#define __DISCO_H__
#include <string>
#include <iostream>

typedef struct partition {
        char part_status;
        char part_type;
        char part_fit;
        int part_start;
        int part_size;
        char part_name[16];
    } partition;


typedef struct mbr {
        int size;
        time_t hora;
        int mbr_disk_signature;
        char disk_fit;
        partition* mbr_partition_1;
        partition* mbr_partition_2;
        partition* mbr_partition_3;
        partition* mbr_partition_4;

        /* Otros commandos a implementar */
    } mbr;


class Disco{
    public:
    typedef struct MKDISK_PARAM {
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
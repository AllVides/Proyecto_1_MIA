#include "../include/parse.h"
#include "../include/myUtil.h"
#include "../include/disco.h"
#include "../include/formato.h"
#include <stdio.h>
#include <cctype>
#include <cstring>
#include <iostream>

void Parse::selector(int num, char **comandos)
{
    comandos[1] = MyUtil::aLower(comandos[1]);
    printf("%s\n", comandos[1]);

    if(strcmp("mkdisk", comandos[1]) == 0){
        printf("hola crear\n");
        Disco crear;
        crear.makedisk(comandos, num);
        
   }else if (strcmp("rmdisk", comandos[1]) == 0){
        printf("hola remueve\n");
        Disco rmv;
        rmv.removedisk(comandos, num);
   }else if (strcmp("fdisk", comandos[1]) == 0){
        printf("hola formatdisk\n");
        Formato frmt;
        frmt.formatdisk(comandos, num);
   }else{
        printf("fallo we, fallo\n");
   }
}
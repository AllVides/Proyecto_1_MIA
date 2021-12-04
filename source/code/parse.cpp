#include "../include/parse.h"
#include "../include/myUtil.h"
#include "../include/disco.h"
#include <stdio.h>
#include <cctype>
#include <cstring>
#include <iostream>

void Parse::selector(int num, char **comandos)
{
    comandos[1] = MyUtil::aMayus(comandos[1]);
    printf("%s;\n", comandos[1]);

    if(strcmp("MKDISK", comandos[1]) == 0){
        printf("hola crear");
        Disco crear;
        crear.makedisk(comandos, num);
        
   }else if (strcmp("RMDISK", comandos[1]) == 0){
        printf("hola remueve");
        Disco rmv;
        rmv.removedisk(comandos, num);
   }
}
#include <stdio.h>
#include <cctype>
#include <iostream>
#include <cstring>
#include "../include/myUtil.h"

char* MyUtil::aMayus(char *palabra)
{
    if (palabra == NULL) {return NULL; }
    for (int i = 0; i < strlen(palabra); i++){
        palabra[i] = toupper(palabra[i]);
    }
    return palabra;
}
#include <stdio.h>
#include <cctype>
#include <iostream>
#include <cstring>
#include "../include/myUtil.h"

char* MyUtil::aLower(char *palabra)
{
    if (palabra == NULL) {return NULL; }
    for (int i = 0; i < strlen(palabra); i++){
        palabra[i] = tolower(palabra[i]);
    }
    return palabra;
}

bool MyUtil::IsSpace(char i){
    return i == ' ';
}
#include "../include/parse.h"
#include "../include/myUtil.h"
#include "../include/disco.h"
#include "../include/formato.h"
#include <stdio.h>
#include <cctype>
#include <cstring>
#include <iostream>
#include <fstream>

using namespace std;

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
   }else if (strcmp("exec", comandos[1]) == 0){
          printf("hola exec\n");
          exec(num, comandos);
   }else if (strcmp("pause", comandos[1]) == 0){
          printf("hola pausa\n");
          cout << "presiona enter para continuar: \n";
          int c;
          cin >> c;
   }else{
        printf("fallo we, fallo\n");
   }
}

void Parse::exec (int num, char **command)
{
     std::string para;
     std::string token;
     std::string delimiter = "~:~";
     std::string path = "";
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
                    cout << para<<"\n";
               }
          if (token == "-path"){
               
               path = para;
          }else{
               std::cout << "comando no reconocido\n";
          }
     }

     string lina;

     std::ifstream ayo(path);

     // Use a while loop together with the getline() function to read the file line by line
     while (getline (ayo, lina)) {
          // Output the text from the file
          if ( lina.back() == '\n' || lina.back() == '\r'){
               lina = lina.substr(0, lina.length()-1 );
          }
          if (lina.empty()){
               cout << "linea en blanco\n";
               continue;
          }
          if ( !lina.empty() ){
               if (lina.back() == '\r' || lina.back() == '\n'){
                    lina = lina.substr(0, lina.length()-1);
               }
          }
          if (lina.empty()){
               cout << "linea en blanco\n";
               continue;
          }
          if (lina[0] == '#' || (lina[0]=='/' && lina[1]=='/')){
               cout<< lina << "\n";
               continue;
          }
          cout << lina;
          std::string cmd = "./main " + lina;
          system(cmd.c_str());
     }

// Close the file
     ayo.close(); 
}
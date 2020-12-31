#include "moduloA.h"
#include "moduloB.h"
#define BUF_SIZE 1024


int main(){
    
    char comand[BUF_SIZE];
    char filename[BUF_SIZE];
    char a = ' ', b = ' ', c = ' ';
    int tam_name, tam_comand;


    if(fgets(comand, BUF_SIZE, stdin) == NULL) return 0;
    sscanf(comand,"shafa %s -m %c",filename,&a);
    tam_name = strlen(filename);
    tam_comand = strlen(comand);
    if(tam_comand == 12 + tam_name){
    if ( a == 'f') printf("A");
    if (a == 't') exec_moduloB(filename);}


    return 0;
}
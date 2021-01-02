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
    if ( a == 'f') exec_moduloA(filename, 65536);
    if (a == 't') exec_moduloB(filename);
    } else {
        sscanf(comand,"shafa %s -m %c -%c %c",filename,&a,&b,&c);
        if(a == 'f' && b == 'b' && c == 'K') exec_moduloA(filename, 655360);
        if(a == 'f' && b == 'b' && c == 'm') exec_moduloA(filename, 8388608);
        if(a == 'f' && b == 'b' && c == 'M') exec_moduloA(filename, 67108864);


    }

    return 0;
}
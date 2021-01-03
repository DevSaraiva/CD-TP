#include <stdio.h>

int abrirFicheiro(){

    char texto[10000];
    int i=0;

    FILE *file;
    file=fopen("aaa.txt","r");

    fscanf(file, "%s", texto);
    printf("%s\n", texto);
}
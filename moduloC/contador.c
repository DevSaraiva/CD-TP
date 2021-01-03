//bibliotecas
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
 
int contSimbSep(void){
    //variáveis
    FILE *fp;
    char text[1000];
    int i, j, contador=0;/*Variáveis para controlar o loop principal, secundário e a quantidade de simbolos de separacao, respectivamente*/
    char simbSep[] = "@";//vetor de vogais
    
    //funcao para abrir e ler o ficheiro
    fp=fopen("aaa.txt.cod","r");  
    printf("%s",fgets(text,1000,fp));

    fclose(fp);
 
    //contagem de simbolos de separadores do ficheiro .cod
    for (i=0;i<strlen(text) && contador<4;i++){
        for (j=0;j<strlen(simbSep);j++){
            if (text[i] == simbSep[j]){
                contador++;
            }
        }
    }
    int ascii[255];
    char prox;
    int taminicial=i;
    for(j=0;j<255;j++){
        ascii[j]=0;
    }
    for(j=0;i<strlen(text) && j<255; i++){
        //ascii[j]=0;
        prox=text[i+1];
        if(text[i]==';' && (prox==';'|| prox=='@')){
            ascii[j]= -1;
            j++;
        }
        if(text[i]!=';'){
            if(ascii[j]>0){
                ascii[j]*=10;
                ascii[j]+=(text[i]-48);
                
             }
            else ascii[j]=text[i]-48;
            
            if(prox==';') j++;    
        }
    }

    //Verificar se guardou os espacos e os numeros binaros 
    for(j=0; j<255; j++){
        printf("%d,", ascii[j]);
    }
    
 
    return 0;
}

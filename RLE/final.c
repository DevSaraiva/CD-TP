#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>

int excecao(char* arr, int i){
    if(arr[i] == '{' && arr[i+1] == '0' && arr[i+2] == '}') return 1;
    else return 0;
    }

int findSubString(char original[],char toFind[] )
{
    size_t n = strlen( original );
    size_t m = strlen( toFind );
    int success = -1;

    if (!( n < m ))
    {
        n = n - m + 1;

        for ( size_t i = 0; success == -1 && i < n; i++ )
        {
            size_t j = 0;
            while ( j < m && original[i+j] == toFind[j] ) j++;

            if ( j == m ) success = i;
        }
    }

    return success;
}
/*
void main(char* nome_source){
    FILE *source = fopen(nome_source,"rb");
    FILE *destino = fopen(nome_source.rle,"wb");
    if(source == NULL){
        printf("O ficheiro de origem encontra-se vazio.\n");
}
*/
int conta_simbolos(char* arr){
    int sum = 0;
    int comprimento = strlen(arr);
    for (int i = 0; i < comprimento;i++){
        if(arr[i] == '{' && arr[i+2] == '}'){
            sum++;
            i+=5;
        }
        else if(arr[i] == '{' && arr[i+3] == '}'){
            sum++;
            i+=6;
        } else if(arr[i] == '{' && arr[i+4] == '}'){
            sum++;
            i+=7;
        }
        else sum++;
    }
    return sum;
}


int compressao(Buffer origem, Buffer comprimido){  
    int simb_original = conta_simbolos(origem.array); 
    int simb_comprimido = conta_simbolos(comprimido.array);
    printf("Simbolos original: %d\n",simb_original);
    printBuff(&comprimido);
    printf("Simbolos comprimido: %d\n",simb_comprimido);

    int res = (100*(simb_original - simb_comprimido)) / simb_original;
    printf("Compressao de %d%%\n",res);
    return res;
}

void main(FILE* source, FILE* destino) { 
    source = fopen("Test.txt", "rb");
    destino = fopen("Dest.txt", "wb");
    int zero = 0;
    int i = 0;
    char atualChar; 
    char proxChar;     
    int count = 1;
    Buffer origem;
    initBuffer(&origem,256);
    char c;
    while(c != EOF){
        c = fgetc(source);
        insertBuffer(&origem,c);
    }

while(origem.array[i+1] != '\0') {

     atualChar = origem.array[i];
     proxChar = origem.array[i+1];

         
        if(excecao(origem.array,i) == 1) {
            int count_exc = 1;
            
            while(excecao(origem.array,i)) {                                                      
                   int indice = findSubString(origem.array,"{0}₁");             // for(i = 0; origem.array[i+1] != '\0';i++){
                    if(origem.array[indice] == origem.array[i+6]){
                        count_exc++;
                        i+=6;
                    }
                    else {
                        fprintf(destino,"{0}₁");
                        fprintf(destino,"{0}₁");
                        fprintf(destino,"{%d}₁",count_exc);
                        count_exc = 1;
                        i = i + 5;
            }
    }
}                    
        if(atualChar == proxChar){
            count++;
        }
        else {
            if(count <= 3) {
            for(int k = 0; k < count; k++){
                if(atualChar != '{')
                fprintf(destino,"%c",atualChar);
           }
        }
        else{
            fprintf(destino,"{%d}₁",zero);
            fprintf(destino,"%c",atualChar);
            fprintf(destino,"{%d}₁",count);
             }
                count = 1;
            }
        i++;
     }  
    fclose(destino);
    Buffer comprimido;
    initBuffer(&comprimido,256);
    char ch;
    while(ch != EOF){
        if(ch != ' '){
        ch = fgetc(destino);
        insertBuffer(&comprimido,ch);
        }
    }
    compressao(origem,comprimido);
}





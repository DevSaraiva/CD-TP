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


int compressao(Buffer origem, int simb_comprimido){   //, char* original)
    int simb_original = conta_simbolos(origem.array) - 1; 
    //printf("Simbolos original: %d\n",simb_original);
    //printf("Simbolos comprimido: %d\n",simb_comprimido);

    int res = (100*(simb_original - simb_comprimido)) / simb_original;
    if(((100*(simb_original - simb_comprimido)) % simb_original) >= 0.5){
        res++;
    }
    //printf("Compressao de %d%%\n",res);
    return res;
}

int main() { 
    FILE* source;
    FILE* destino;
    source = fopen("Test.txt", "rb");
    destino = fopen("Dest.txt", "wb");
    int i = 0;
    char atualChar; 
    char proxChar;     
    int count = 1;
    int n_simbolos = 0;
    Buffer origem;
    initBuffer(&origem,256);
    char c;
    while(c != EOF){
        c = fgetc(source);
        insertBuffer(&origem,c);
    }
    //printBuff(&origem);
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
                        fprintf(destino,"{0}₁{0}₁{%d}₁",count_exc);
                        n_simbolos +=3;
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
                if(atualChar != '{'){
                fprintf(destino,"%c",atualChar);
                n_simbolos++;
                }
           }
        }
        else{
            fprintf(destino,"{0}₁%c{%d}₁",atualChar,count);
            n_simbolos +=3;
             }
                count = 1;
            }
        i++;
     }  
    fclose(destino);
    compressao(origem,n_simbolos);
    return 0;
}





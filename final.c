#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>
#include "fsize.h"

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








int rle(Buffer origem,char nome[],unsigned long tamanho_bloco, int index) { 
    nome = "Test.txt";
    FILE* source;
    FILE* destino;
    source = fopen(nome, "rb");
    destino = fopen("Dest.txt", "wb");
    char atualChar; 
    char proxChar;
    int i = 0;     
    int count = 1;
    int n_simbolos = 0;
    int ind = 0;
    Buffer bloco_temp;

    while(ind != index * FSIZE_DEFAULT_BLOCK_SIZE){
    
    initBuffer(&bloco_temp,256);
    insertBuffer(&bloco_temp,origem.array[ind]);
    
    ind++;
    }

while(bloco_temp.array[i+1] != '\0') {

     atualChar = bloco_temp.array[i];
     proxChar = bloco_temp.array[i+1];

         
        if(excecao(bloco_temp.array,i) == 1) {
            int count_exc = 1;
            
            while(excecao(bloco_temp.array,i)) {                                                      
                   int indice = findSubString(bloco_temp.array,"{0}₁");             // for(i = 0; origem.array[i+1] != '\0';i++){
                    if(bloco_temp.array[indice] == bloco_temp.array[i+6]){
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
    compressao(bloco_temp,n_simbolos);
    return 0;
}


int main(){

    unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block, block_size;
    FILE *fp;
    Buffer origem;
    initBuffer(&origem,256);
    char c;
    char filename[] = "Test.txt";
    fp = fopen(filename, "rb");
    while(c != EOF){
        c = fgetc(fp);
        insertBuffer(&origem,c);
    }

    // Using function fsize() when file is already opened
    block_size = 65536;
    n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);   // numero blocos
    total = (n_blocks-1) * block_size + size_of_last_block;         // tamanho do ficheiro


    for(int i = 1; i < n_blocks + 1; i++){
        
        if(i != n_blocks) rle(origem,filename,block_size,i);
        else rle(origem,filename,size_of_last_block,i);
    }

    printf("\n File: aaa.txt (file already opened)");
    printf("\n %lld blocks of %lu bytes + 1 block of %lu bytes", n_blocks-1, block_size, size_of_last_block);
    printf("\n File size = %llu bytes\n", total);
    fclose(fp);

    // Using function fsize() when file is not opened
    block_size = FSIZE_DEFAULT_BLOCK_SIZE;
    n_blocks = fsize(NULL, "bbb.zip", &block_size, &size_of_last_block);
    total = (n_blocks-1) * block_size + size_of_last_block;
    printf("\n File: bbb.zip");
    printf("\n %lld blocks of %lu bytes + 1 block of %lu bytes", n_blocks-1, block_size, size_of_last_block);
    printf("\n File size = %llu bytes\n", total);

    return(0);
}

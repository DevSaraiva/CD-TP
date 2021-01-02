#ifndef moduloA
#define moduloA

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>
#include "fsize.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>
#include <time.h>

//Função para averiguar um caso de exceção ({0}₁) para a compressão RLE.
int excecao(char* arr, int i){
    if(arr[i] == '{' && arr[i+1] == '0' && arr[i+2] == '}') return 1;
    else return 0;
    }

//Função que dada um string principal, procura uma substring devolvendo um inteiro que sinaliza o seu sucesso.
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
//Função que conta o número de símbolos duma string devolvendo esse número.
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

//Função que calcula a compressão de um ficheiro RLE em relação ao original.
int compressao(Buffer origem, int simb_comprimido){ 
    int simb_original = conta_simbolos(origem.array) - 1; 
    int res = (100*(simb_original - simb_comprimido)) / simb_original;
    if(((100*(simb_original - simb_comprimido)) % simb_original) >= 0.5){
        res++;
    }
    return res;
}

//Função que verifica se existem elementos repetidos numa string.
int verifica_repetidos (char elems[], int n_elems_dif,char c){
    for(int i = 0; i < n_elems_dif; i++){
        if (elems[i] == c) {
            return i;
        } 
    }
    return -1;
}
//Função que calcula e retorna o número de elementos repetidos num array.
int calcula_n_rep (char a[],int index){
    int i=1, b=0, n=0;
    while (a[index+i]!='}'){
        i++;
    }
    i--;
    while (i > 0) {
        n += (a[i+index]-48) * pow (10,b);
        b++; i--;
    }
    return n;
}

//Função que dado um buffer calcula a frequência dos símbolos e mete-os num array ordenado pelo seu código ASCII.
void freq(Buffer bloco,int reps[],int i_block,int block_size,int n_blocks,int total) {
     
       int i = (i_block-1)*block_size;
       int fim ;
       if (i_block<n_blocks) fim = i_block*block_size;
       else if (i_block==n_blocks) fim = total;
       while(i < fim) {
        char n;
        char n1;
        char n2;
        int in;
        int c2a;
        int count = 0;
        char string1[3];
        char string2[4];
        
        if(bloco.array[i] == '{'){
        if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}' && bloco.array[i+6] == '{' && bloco.array[i+7] == '0' && bloco.array[i+8] == '}') { 
            int in = calcula_n_rep(bloco.array,i+12);
            c2a = bloco.array[i+1];
            count += in;
            reps[c2a] += count;
            i += 17; 
    
        } else if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}') {
                if(bloco.array[i+9] == '}') {
                    n = bloco.array[i+8];
                    in = n - '0';
                    i += 6;
                    c2a = bloco.array[i];
                    count += in;
                    reps[c2a] += count;
                    i += 6; 
                } else if(bloco.array[i+10] == '}'){
                    n = bloco.array[i+8];
                    n1 = bloco.array[i+9];
                    string1[0] = n, string1[1] = n1; string1[2] = '\0';
                    int x = atoi(string1);
                    i += 6;
                    c2a = bloco.array[i];
                    count += x;
                    reps[c2a] += count;
                    i += 7; 
                 }else if(bloco.array[i+11] == '}'){
                    n = bloco.array[i+8];
                    n1 = bloco.array[i+9];
                    n2 = bloco.array[i+10];
                    string2[0] = n, string2[1] = n1;string2[2] = n2;  string2[3] = '\0';
                    int x = atoi(string2);
                    i += 6;
                    c2a = bloco.array[i];
                    count += x;
                    reps[c2a] += count;
                    i += 8; 
                } 
            } 
         } else {
             c2a = bloco.array[i];
             reps[c2a]++;
        }
        i++;
    } 
}

//Função que insere um int num dado buffer.
void insertBufferInt (Buffer *a, int x) {
    int someInt = x;
    char str[12];
    sprintf(str, "%d", someInt);
    int i=0;
    while (str[i]!='\0'){
        insertBuffer (a,str[i]);
        i++;
    }
}

//Função que insere num buffer final as frequências de cada bloco.
void freqBlock(Buffer *final, int reps[]){
    insertBufferInt(final,reps[0]);
    insertBuffer(final,';');
    int i=1;
    while (i<256){
        if (reps[i]!=reps[i-1]) 
            insertBufferInt(final,reps[i]);
        insertBuffer (final,';');
        i++;
    }
}

// Função que escreve a codificação no ficheiro ".freq".
void write_file_buffer_ParteA(Buffer * final, char fileName[]){
  
  int i = 0;
  while(fileName[i] != '\0'){
    i++;
  }
  int last = i ;
  i = 0;
  char name[25];

  while(i <= last){
    name[i] = fileName[i];
    i++;
  }
  char termination[40] = ".freq";
  strcat(name,termination);
  FILE * file = fopen(name,"w");
  fprintBuff(final,file);
}

//Função que escreve num ficheiro ".freq" a frequência de cada símbolo conforme as especificações do enunciado.
void rle_to_freq(char filename[], unsigned long block_size){
    FILE* source = fopen(filename, "rb");
    Buffer bloco_rle;
    initBuffer(&bloco_rle, 256); 
    char c;
    while(c != EOF){             
        c = fgetc(source);
        insertBuffer(&bloco_rle,c);
    }
    unsigned long long total;
    long long n_blocks;
    long size_of_last_block;
    n_blocks = fsize(source, NULL, &block_size, &size_of_last_block);  
    total = (n_blocks-1) * block_size + size_of_last_block;         
    int i_bloco = 1;
    int reps[256];
    int j;
    Buffer buffer_final;
    initBuffer (&buffer_final, 150);
    insertBuffer(&buffer_final,'@');
    insertBuffer(&buffer_final,'R');
    insertBuffer(&buffer_final,'@');
    insertBufferInt(&buffer_final,n_blocks);
    while (i_bloco <= n_blocks){
        insertBuffer(&buffer_final,'@');
        for (j=0;j<256;j++) reps[j]=0;
        freq(bloco_rle,reps,i_bloco,block_size,n_blocks,total);
        if (i_bloco < n_blocks) insertBufferInt(&buffer_final,block_size);
        else insertBufferInt(&buffer_final,size_of_last_block);
        insertBuffer(&buffer_final,'@');
        freqBlock(&buffer_final,reps);
        i_bloco++;
    }
    insertBuffer(&buffer_final,'@');
    insertBuffer(&buffer_final,'0');
    printBuff(&buffer_final);
    write_file_buffer_ParteA(&buffer_final,filename);
}

//Função que calcula e escreve num ficheiro a codificação RLE por blocos.
int rle_aux(Buffer bloco_temp, char* filename, int i, int fim) { 
    FILE* destino = fopen(filename, "wb");
    char atualChar; 
    char proxChar;  
    int n_simbolos = 0;
    int count = 1;
    int compression;
while(i < fim) { 
     atualChar = bloco_temp.array[i];
     proxChar = bloco_temp.array[i+1];

        if(excecao(bloco_temp.array,i) == 1) {
            int count_exc = 1;
            
            while(excecao(bloco_temp.array,i)) {                                                      
                   int indice = findSubString(bloco_temp.array,"{0}₁");        
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
//Função que itera a função rle_aux para obter a compressão RLE bloco a bloco.
int rle(Buffer origem,char filename[],unsigned long block_size,int total, int n_blocks, int* block_compression) { //
       int i = 0;
       int fim;
       char terminacao_rle[40] = ".rle";
       strcat(filename,terminacao_rle);

 for(int i_block = 1; i_block <= n_blocks; i_block++){
     i = (i_block-1)*block_size;
     if (i_block<n_blocks) fim = i_block*block_size;
    else fim = total;
       //block_compression[i_block] = rle_aux(origem,filename,i,fim);
       rle_aux(origem,filename,i,fim);
 }
    return 0;
}

//Função principal do módulo A.
int exec_moduloA(char* filename, unsigned long block_size){ 
    clock_t begin = clock();
    unsigned long long total;
    long long n_blocks;
    unsigned long size_of_last_block;
    int block_compression[n_blocks];
    FILE *fp;
    Buffer origem;
    initBuffer(&origem,256);
    char c;
    char filename_txt[40];
    strcpy(filename_txt,filename);

    fp = fopen(filename_txt, "rb");
    while(c != EOF){
        c = fgetc(fp);
        insertBuffer(&origem,c);
    }

    //block_size = 65536;
    n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);   // numero blocos
    total = (n_blocks-1) * block_size + size_of_last_block;         // tamanho do ficheiro
    //int* ptr = 
    rle(origem,filename_txt,block_size,total,n_blocks,block_compression);
    fclose(fp);
    //printf("%d", ptr[0]);

    //char filename_freq[] = "aaa.txt.rle";
    //rle_to_freq(filename);
    char filename_freq[40];
    strcpy(filename_freq, filename);
    char terminacao_rle[] = ".rle";
    strcat(filename_freq,terminacao_rle); // tenho que adicionar .rle ao filename original qnd tiver o interpretador 
    rle_to_freq(filename_freq,block_size);

    clock_t end = clock();
    double time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    double time_spent_ms = time_spent * 1000;
    printf("\nRodrigo Rodrigues (a93201) & Rui Monteiro (a93179), MIEI/CD, 1-jan-2021\n");
    printf("Módulo: f (cálculo das frequências dos símbolos)\n");
    printf("Número de blocos: %lld\n",n_blocks);
    if(n_blocks == 1) {
        printf("Tamanho dos blocos analisados no ficheiro original:_%lu\n", size_of_last_block);
    } else {
    printf("Tamanho dos blocos analisados no ficheiro original: %lu/%lu\n",block_size,size_of_last_block);
    }
    int sum = 0;
    for(int j = 0; j < n_blocks; j++) {
    //    sum += ptr[j];
    }
    int compressao_media = sum / n_blocks;
    printf("Compressão RLE: %d\n", compressao_media);
    /*
    FILE* ficheiro_rle;
    ficheiro_rle = fopen(filename_freq, "rb");
    int n_blocks_rle = fsize(ficheiro_rle, NULL, &block_size, &size_of_last_block);
    if(n_blocks_rle == 1) {
        printf("Tamanho dos blocos analisados no ficheiro RLE:_%lu bytes\n", size_of_last_block);
    } else {
    printf("Tamanho dos blocos analisados no ficheiro RLE: %lu bytes /%lu bytes\n",block_size,size_of_last_block);
    }
    */
    printf("Tamanho dos blocos analisados no ficheiro RLE: \n");
    printf("Tempo de execução do módulo (milissegundos): %f\n",time_spent_ms);

    //char terminacao_rle_print[40] = ".rle";
    ///strcat(filename_txt,terminacao_rle_print);
    char terminacao_freq_print[40] = ".freq";
    strcat(filename_freq,terminacao_freq_print);

    printf("Ficheiros gerados: %s,%s",filename_txt,filename_freq);
}

#endif //moduloA
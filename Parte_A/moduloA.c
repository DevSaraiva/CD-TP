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

int verifica_repetidos (char elems[], int n_elems_dif,char c){
    for(int i = 0; i < n_elems_dif; i++){
        if (elems[i] == c) {
            return i;
        } 
    }
    return -1;
}

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


void freq(Buffer bloco,int reps[],int i_block,int block_size,int n_blocks,int total) {
     
     //int elems[];
    //int visited = -1;
       int i = (i_block-1)*block_size;
       int fim ;
       if (i_block<n_blocks) fim = i_block*block_size;
       else if (i_block==n_blocks) fim = total;
       while(i < fim) {
        //printf("%c ",bloco.array[i]);
        char n;
        char n1;
        char n2;
        int in;
        int c2a;
        int count = 0;
        char string1[3];
        char string2[4];
        

        if(bloco.array[i] == '{'){
        if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}' && bloco.array[i+6] == '{' && bloco.array[i+7] == '0' && bloco.array[i+8] == '}') { // {0} {00} {000}
        //printf("ola\n");
        //printf("%c\n",bloco.array[i+12]);
        int in = calcula_n_rep(bloco.array,i+12);
        //printf("%d\n",in);
        //in = n - '0';
        c2a = bloco.array[i+1];
        count += in;
        reps[c2a] += count;
        
        i += 17; // i += 14; 
    
        } else if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}') {
                //printf("ola\n");
                if(bloco.array[i+9] == '}') {
                    n = bloco.array[i+8];
                    in = n - '0';
                    i += 6;

                    c2a = bloco.array[i];
                    count += in;
                    reps[c2a] += count;

                    i += 6; //i += 7;
                } else if(bloco.array[i+10] == '}'){
                    n = bloco.array[i+8];
                    n1 = bloco.array[i+9];
                    string1[0] = n, string1[1] = n1; string1[2] = '\0';
                    int x = atoi(string1);
                    i += 6;
                    c2a = bloco.array[i];
                    count += x;
                    reps[c2a] += count;
                    i += 7; //i += 8;
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
                    i += 8; //i += 9;
                } 
                //in = calcula_n_rep(bloco.array,7);
                //i += 6;

                //c2a = bloco.array[i];
                //count += in;
                //reps[c2a] += count;

                //i += 6; //i += 7;
            } 
         } else {
             c2a = bloco.array[i];
             //count++;
             reps[c2a]++;
        }
        i++;
        
    } 
    //int a=0;
    //while(a<256){
        //printf("%d ;",reps[a]);
      //  a++;
    //}
}


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
    //printBuff(final);
}

// Função que escreve a codificação no ficheiro .freq
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
  char termination[] = ".freq";
  strcat(name,termination);
  FILE * file = fopen(name,"w");
  fprintBuff(final,file);
}

void rle_to_freq(char filename[]){
    //char filename[] = "aaa.txt.rle";
     FILE* source = fopen(filename, "rb");
    Buffer bloco_rle;
    initBuffer(&bloco_rle,256); //FIXME tamanho do bloco
    char c;
    while(c != EOF){             // while até ao fim do bloco
        c = fgetc(source);
        insertBuffer(&bloco_rle,c);
    }
    unsigned long long total;
    long long n_blocks;
    long size_of_last_block;
    unsigned long block_size = 991;
    n_blocks = fsize(source, NULL, &block_size, &size_of_last_block);   // numero blocos
    total = (n_blocks-1) * block_size + size_of_last_block;         // tamanho do ficheiro
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
        if (i_bloco < n_blocks)     insertBufferInt(&buffer_final,block_size);
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
int rle_aux(Buffer bloco_temp, char* filename, int i, int fim) { //FIXME - FAZER A EXCEÇAO dos 5% na main, tendo em conta que e´ so´ pro primeiro BLOCO, temos q fazer um IF 1º bloco_temp e compressao < 5% then APAGAR O FICHEIRO.Rle
    FILE* destino = fopen("Dest.txt", "wb");         // FIXME - Temos tambem que implentar depois uma maneira de forçar a compressao mesmo que ela sejam menor q 5% conforme o enunciado atraves do interpretador
    //int i = 0; 
    char atualChar; 
    char proxChar;  
    int n_simbolos = 0;
    int count = 1;
    
while(i < fim) { // aqui antes era i + 1 
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

int rle(Buffer origem,char nome[],unsigned long block_size,int total, int n_blocks) { //(Buffer bloco,int reps[],int i_block,int block_size,int n_blocks,int total)
       int i = 0;
       int fim;

 for(int i_block = 1; i_block <= n_blocks; i_block++){
     i = (i_block-1)*block_size;
     if (i_block<n_blocks) fim = i_block*block_size;
    else fim = total;
       
       rle_aux(origem,nome,i,fim);
 }
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
    char filename_txt[] = "Test.txt";
    fp = fopen(filename_txt, "rb");
    while(c != EOF){
        c = fgetc(fp);
        insertBuffer(&origem,c);
    }
    
    block_size = 65536;
    n_blocks = fsize(fp, NULL, &block_size, &size_of_last_block);   // numero blocos
    total = (n_blocks-1) * block_size + size_of_last_block;         // tamanho do ficheiro
    
    rle(origem,filename_txt,block_size,total,n_blocks);
    fclose(fp);


    //char filename[] = "aaa.txt.rle";
    //rle_to_freq(filename);
    char filename[] = "Dest.txt";
    rle_to_freq(filename);
    
}

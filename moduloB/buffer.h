#ifndef buffer
#define buffer


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct {
  char *array;
  int used;
  int size;
  int elem;
} Buffer ;

// Funções de inicialização, gestão , cópia e libertação de memória em relação a buffers

void initBuffer(Buffer *a, int initialSize) {
  a->array = malloc(initialSize * sizeof(char));
  a->used = 0;
  a -> elem = 0;
  a->size = initialSize;
}

void insertBuffer(Buffer *a, char element) {
 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char));
  }
  a->array[a->used++] = element;
  if(element == ';') a -> elem++;
}

void freeBuffer(Buffer *a) {
  free(a->array);
  a->array = NULL;
  a->used = a->size = 0;
}

Buffer  read_file_buffer(Buffer * a, char txt[]){
    
    char c;
    initBuffer(a, 150);
    FILE * file = fopen(txt, "rb");
    while(c != EOF){
        c = fgetc(file);
        insertBuffer(a, c);
        
    }
fclose(file);

return *a;
}

// Função que escreve o buffer no ficheiro

int fprintBuff(Buffer *a, FILE * file){
   
   int i = 0;
   char c;
   while(a->array[i] != '\0'){
       c = a->array[i];
       fputc(c,file);
       i++;
   }
    
    
    
    return 0;
}


// Função que escreve a codificação no ficheiro

void write_file_buffer(Buffer * final, char fileName[],char name[]){
  
  int i = 0;
  while(fileName[i] != '\0'){
    i++;
  }
  int last = i-5;
  i = 0;

  while(i < last){
    name[i] = fileName[i];
    i++;
  }
  name[i] = '\0';

  char termination[] = ".cod";
  strcat(name,termination);
  FILE * file = fopen(name,"w");
  fprintBuff(final,file);
  

}


// Função que faz print no buffer

int printBuff(Buffer *a){
   
    int i = 0;
   char c;
   while(a->array[i] != '\0'){
       c = a->array[i];
       printf("%c",c);
       i++;
   }
    
    
    
    return 0;
}

// Função que copia de um buffer a para outro b N elementos a partir de determinada posição '@'
int copyNelments(Buffer *a, Buffer *b, int N, int initial_pos){
    int cont1 = 0;
    int cont2 = 0;
    int i = 0;
    
    while(cont1 < initial_pos){
        if(a -> array[i] == '@') cont1++;
        i++;
        if(cont1 == initial_pos) i--;
    }
    
    while(cont2 < N && i < a->used){
        if(a->array[i] == '@') {
            cont2++;
            insertBuffer(b,a->array[i]);
            i++;
           while(a -> array[i] != '@'){
               insertBuffer(b,a->array[i]);
               i++;
           }
        } 
    
    } 
    return 0;
   }

// A Função swapBuffer recebe um buffer e duas posições do buffer e troca o que está nessas duas posições
void swapBuffer (Buffer *a,int i,int y){ 
   int temp;
   temp=a->array[i];
   a->array[i]=a->array[y];
   a->array[y]=temp;
}



int calculaTamanhoBloco (Buffer *a,int i_bloco){
    int i=0, b=0, tam=0, n_a =0;
    while (n_a < (i_bloco+1)*2){
        if (a->array[i]=='@') { 
            //printf(" %c \n",a->array[i]);
              n_a++;
        }
        i++;
    }
    i--;i--;
    while (a->array[i]!='@') {
        tam += (a->array[i]-48) * pow (10,b);
        b++; i--;
    }
    return tam;
}



#endif //buffer

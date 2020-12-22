#ifndef buffer
#define buffer


#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *array;
  int used;
  int size;
} Buffer ;

// Funções de inicialização, gestão , cópia e libertação de memória em relação a buffers

void initBuffer(Buffer *a, int initialSize) {
  a->array = malloc(initialSize * sizeof(char));
  a->used = 0;
  a->size = initialSize;
}

void insertBuffer(Buffer *a, char element) {
 
  if (a->used == a->size) {
    a->size *= 2;
    a->array = realloc(a->array, a->size * sizeof(char));
  }
  a->array[a->used++] = element;
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

    printf("Size:%d usedSize:%d \n",a->size,a->used);
return *a;
}

// Função que escreve que faz print no buffer

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
        printf("primeiro \n");
        if(cont1 == initial_pos) i--;
    }
    
    while(cont2 < N && i < a->used){
        if(a->array[i] == '@') {
            cont2++;
            insertBuffer(b,a->array[i]);
            i++;
            printf("segundo \n");
           while(a -> array[i] != '@'){
               insertBuffer(b,a->array[i]);
               i++;
               printf("terceiro \n");
           }
        } 
    
    } 

   }



#endif //buffer
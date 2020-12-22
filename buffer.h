#ifndef buffer
#define buffer


#include <stdio.h>
#include <stdlib.h>

typedef struct {
  char *array;
  int used;
  int size;
} Buffer ;

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

Buffer read_file_buffer(Buffer a, char txt[]){
    
    char c;
    initBuffer(&a, 150);
    FILE * file = fopen(txt, "rb");
    while(c != EOF){
        c = fgetc(file);
        insertBuffer(&a, c);
        
    }

    printf("Size:%d usedSize:%d \n",a.size,a.used);
return a;
}

#endif //buffer
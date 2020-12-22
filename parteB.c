#include "buffer.h"

int printBuff(Buffer *a){
   
    int i = 0;
   char c;
   while(a->array[i + 1] != '\0'){
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
        i++;
       
    } 

   }



int main(){
   Buffer initial_buffer = read_file_buffer(initial_buffer,"aaa.txt.rle.freq");
   Buffer final_buffer;
   initBuffer(&final_buffer,150);
   copyNelments(&initial_buffer, &final_buffer,2,0);
   printBuff(&final_buffer);

   
   
    
    
    return 0;
}


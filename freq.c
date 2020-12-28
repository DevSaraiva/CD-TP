#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>


int freq() {
    FILE* source = fopen("Dest.txt", "rb");

    
    Buffer bloco;
    initBuffer(&bloco,256); //FIXME tamanho do bloco
    char c;
    while(c != EOF){             // while até ao fim do bloco
        c = fgetc(source);
        insertBuffer(&bloco,c);
    }

    int fr[bloco.used];
    int visited = -1;

    for(int i = 0; i < bloco.used; i++){
        int count = 1;
        for(int j = i + 1; j < bloco.used; j++){
            if(bloco.array[i] == bloco.array[j]){
                count++;
                fr[j] = visited;
            }
        }
        if(fr[i]!=visited)
            fr[i] = count;
    }
     printf("---------------------\n");    
    printf(" Element | Frequency\n");    
    printf("---------------------\n");    
    for(int i = 0; i < bloco.used; i++){    
        if(fr[i] != visited){    
            printf("    %d", bloco.array[i]);    
            printf("    |  ");    
            printf("  %d\n", fr[i]);    
        }    
    }    
    printf("---------------------\n");    
    return 0;    
}    


int main(){
    freq();
    return 0;
}
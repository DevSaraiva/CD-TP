#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>

int freq(char filename[]) {
    FILE* source = fopen(filename, "rb");
    int count = 0;
    

    Buffer bloco;
    initBuffer(&bloco,256); //FIXME tamanho do bloco
    char c;
    while(c != EOF){             // while até ao fim do bloco
        c = fgetc(source);
        insertBuffer(&bloco,c);
    }

    int fr[bloco.used];
    int visited = -1;

    for(int i = 0; i < bloco.used; i++) {
        
        char n;
        char n1;
        char n2;
        int in;
        char string1[3];
        char string2[4];
        if(bloco.array[i] == '{'){
        if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}' && bloco.array[i+5] == '{' && bloco.array[i+6] == '0' && bloco.array[i+7] == '}' && bloco.array[i+10] == '{' && bloco.array[i+11] == n && bloco.array[i+12] == '}') { // {0} {00} {000}
        in = n - '0';
        i++;
        count += in;
        i += 14; 
        } else if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}') {
                if(bloco.array[i+9] == '}') {
                    n = bloco.array[i+8];
                    in = n - '0';
                    i += 6;
                    count += in;
                    i += 7;
                } else if(bloco.array[i+10] == '}'){
                    n = bloco.array[i+8];
                    n1 = bloco.array[i+9];
                    string1[0] = n, string1[1] = n1; string1[2] = '\0';
                    int x = atoi(string1);
                    i += 6;
                    count += x;
                    i += 8;
                 }else if(bloco.array[i+11] == '}'){
                    n = bloco.array[i+8];
                    n1 = bloco.array[i+9];
                    n2 = bloco.array[i+10];
                    string2[0] = n, string2[1] = n1;string2[2] = n2;  string2[3] = '\0';
                    int x = atoi(string2);
                    i += 6;
                    count += x;
                    i += 9;
                } 
            } 
         } else {
        for(int j = i + 1; j < bloco.used; j++){
            if(bloco.array[i] == bloco.array[j]){
                count++;
                fr[j] = visited;
            }
        }

        if(fr[i]!=visited && fr[i]!='{' && fr[i]!='}') fr[i] = count;
        }
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
    char filename[] = "Dest.txt";
    freq(filename);
}
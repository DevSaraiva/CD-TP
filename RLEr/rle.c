#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"

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

void main() { 
    FILE *source = fopen("Test.txt", "rb");
    FILE *destino = fopen("Dest.txt", "wb");
    int zero = 0;
    int i = 0;
    char atualChar; 
    char proxChar;     
    int count = 1;
    Buffer origem;
    initBuffer(&origem,200);
    char c;
    while(c != EOF){
        c = fgetc(source);
        insertBuffer(&origem,c);
    }
    

while(origem.array[i+1] != '\0') {

     atualChar = origem.array[i];
     proxChar = origem.array[i+1];

         
        if(excecao(origem.array,i) == 1) {
            int count_exc = 1;
            
            while(excecao(origem.array,i)) {                                                      
                   int indice = findSubString(origem.array,"{0}₁"); // for(i = 0; origem.array[i+1] != '\0';i++){
                    if(origem.array[indice] == origem.array[i+6]){
                        count_exc++;
                        i+=6;
                    }
                    else {
                        fprintf(destino,"{0}₁{0}₁{%d}₁",count_exc);
                        count_exc = 1;
                        i+=5;
            }
            //i += 5;                            // i += 5 
    }
}                    
        if(atualChar == proxChar){
            count++;
        }
        else {
            if(count <= 3) {
            for(int k = 0; k < count; k++){
                printf("Count = %d\n", count);
                fprintf(destino,"%c",atualChar);
           }
        }
        else{
            fprintf(destino,"{%d}₁",zero);
            fprintf(destino,"%c",atualChar);
            fprintf(destino,"{%d}₁",count);
             }
                count = 1;
            }
        i++;
     }       
}





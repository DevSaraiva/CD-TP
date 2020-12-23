#include <stdio.h>
#include <stdlib.h>


void main()
{ 
    FILE *source = fopen("Test.txt", "r");
    FILE *destino = fopen("Dest.txt", "w");
    int zero = 0;
    char atualChar; 
    char proxChar;     
    int count = 1;

    while(fread(&atualChar, sizeof(char),1, source) != 0) {
        if (fread(&proxChar, sizeof(char),1, source) == 0){
            if(count<=3){
                for(int i=0;i<count;i++){
                    fprintf(destino,"%c",atualChar);
                }
            }
            else {    // quando um char se repete 4 ou mais vezes
                    fprintf(destino,"{%d}₁",zero);
                    fprintf(destino,"{%c}₁",atualChar);
                    fprintf(destino,"{%d}₁",count);
                }
            break;
        }
        else fseek(source,-1*sizeof(char), SEEK_CUR);

        while (fread(&proxChar, sizeof(char), 1, source) != 0) {
            if (atualChar ==  proxChar) {
                count++;
            } 
            else {
                if(count<=3){
                    for(int i=0;i<count;i++){
                        fprintf(destino,"%c",atualChar);
                    }
                }
                else {
                    fprintf(destino,"{%d}₁",zero);
                    fprintf(destino,"{%c}₁",atualChar);
                    fprintf(destino,"{%d}₁",count);
                }

                count = 1;
                goto OUT;
            }
        }

OUT:fseek(source,-1*sizeof(char), SEEK_CUR); //exit 2° while
    }
}
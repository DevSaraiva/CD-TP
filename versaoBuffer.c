#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "buffer.h"
char *char_to_str(char destino[], char source) 
{ 
	destino[0] = source;	// copy the character into the string 
	destino[1] = '\0';		// null-terminate the string 
 
	return destino;			// common convention for str functions 
} 

int excecao_zero(char atualChar, char proxChar){
    char atualString[5];
           char proxString[5];
           char_to_str(atualString,atualChar);
           char_to_str(proxString,proxChar);
           
           if (strcmp(atualString,"{") == 0){                      // {0
               char atualString_temp[5];
             
               strcpy(atualString_temp,atualString);              // copiei "{" para atualString_temp
               
               char str1[4];           
               if(proxString[0] == '0'){
               strcpy(str1,strcat(atualString_temp,proxString));     // juntei o conteudo de proxString (que deve ser um zero) ao atualString_temp e fica "{0"
                }                                                     // guardei {0 em str1
               char str_zero[4] = "{0";
             
               if (strcmp(str1,str_zero) == 0) return 1;           // se for igual a "{0" entao temos a excecao
               else return 0;                                      // caso contrario nao temos a excecao

           }
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

while(i < origem.used - 1){
    atualChar = origem.array[i];
    proxChar = origem.array[i+1];
    i++;
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




/*
if(atualChar == '{') {
                for(int i=0;i < count;i++){
                char ss[20] = "{0}₁{0}₁{ }";
                printf("%c",ss[14]);
                fprintf(destino,"%s",ss);
            }
           }
   */        



/*
while(fread(&atualChar, sizeof(char),1, source) != 0) {  // quando há algo para ler, ou seja, atualChar nao é "vazio"
        if (fread(&proxChar, sizeof(char),1, source) == 0){  // se o proximo for "vazio", ou seja, nao há mais nada para ler 

            if(atualChar == '{') {
                for(int i=0;i < count;i++){
                char ss[20] = "{0}₁{0}₁{ }";
                printf("%c",ss[14]);
                fprintf(destino,"%s",ss);
            }
           }
           else {
            if(count<=3){
                for(int i=0;i<count;i++){
                    fprintf(destino,"%c",atualChar);
                }
            }
            else {    // quando um char se repete 4 ou mais vezes
                    fprintf(destino,"{%d}₁",zero);
                    fprintf(destino,"%c",atualChar);
                    fprintf(destino,"{%d}₁",count);
                }
            break;
        }
        }
        
        else fseek(source,-1*sizeof(char), SEEK_CUR);

        while (fread(&proxChar, sizeof(char), 1, source) != 0) { // quando o proximo nao é "vazio", ou seja, há mais chars para ler
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
                    fprintf(destino,"%c",atualChar);
                    fprintf(destino,"{%d}₁",count);
                }

                count = 1;
                goto OUT;
            }
        }

OUT:fseek(source,-1*sizeof(char), SEEK_CUR); //exit 2° while
    }
}


*/


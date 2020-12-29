#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include "buffer.h"
#include <math.h>


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
    while (i > index) {
        n += (a[i+index]-48) * pow (10,b);
        b++; i--;
    }
    return n;
}


int freq(char filename[]) {
    FILE* source = fopen(filename, "rb");
    
    Buffer bloco;
    initBuffer(&bloco,256); //FIXME tamanho do bloco
    char c;
    while(c != EOF){             // while até ao fim do bloco
        c = fgetc(source);
        insertBuffer(&bloco,c);
    }

    int reps[256];
    
    int j = 0;
    while(j <= 255){
        reps[j] = 0;
        j++;
    }

    //int elems[];
    //int visited = -1;
       int i = 0;
       while(i < bloco.used) {
        
        char n;
        char n1;
        char n2;
        int in;
        int c2a;
        int count = 0;
        char string1[3];
        char string2[4];
        printf("%d",i);

        if(bloco.array[i] == '{'){
        if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}' && bloco.array[i+6] == '{' && bloco.array[i+7] == '0' && bloco.array[i+8] == '}') { // {0} {00} {000}
        printf("ola\n");
        char n = bloco.array[i+13];
        in = n - '0';
        c2a = bloco.array[i+1];
        count += in;
        reps[c2a] += count;
        
        i += 17; // i += 14; 
    
        } else if(bloco.array[i] == '{' && bloco.array[i+1] == '0' && bloco.array[i+2] == '}') {
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
            } 
         } else {
             c2a = bloco.array[i];
             //count++;
             reps[c2a]++;
        }
        i++;
        
    } 
    printf("%d\n",reps[48]);
    
    return 0;    
}



int main(){
    char filename[] = "Dest.txt";
    char arr[] = "aa936c{0}₁{0}₁{1}₁g648{0}₁b{17}₁akjdaaajdf{0}₁19₁{31}₁fsissyi";
    printf("%c\n",arr[35]);
    int res = calcula_n_rep(arr,35);
    printf("%d\n",res);
    //freq(filename);
}
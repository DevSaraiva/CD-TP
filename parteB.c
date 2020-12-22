#include <math.h>
#include "buffer.h"

int calculaTamanhoBloco (Buffer *a){
    int i=1, b=0, tam=0;
    while (a->array[i]!='@'){
        i++;
    }
    i--;
    while (i>0) {
        tam += (a->array[i]-48) * pow (10,b);
        b++; i--;
    }
    return tam;
}


 int calculaFrequencia (Buffer *a, int indice, int freq_anterior){
    int i=1, b=0, freq=0;
    while (a->array[indice + i]!=';'){
        i++;
    }
    if (i==1) return freq_anterior;
    i--;
    while (i>0) {
        freq += (a->array[i+indice]-48) * pow (10,b);
        b++;i--;
    }
    return freq;
}

 void retiraFreq (Buffer *a,int bloco){
    Buffer aux;
    initBuffer (&aux, 150);
    copyNelments (a, &aux, 2, 1+2*bloco);
    //printBuff (&aux);
    //printf ("\n");
   // printBuff (a);
    //int tamanho = calculaTamanhoBloco(&aux);
    //printf("%i \n",tamanho);
    int frequencia[256];
    int i = 1, j=1;
    while (aux.array[i]!='@'){
        i++;
    }    
    frequencia[0]= calculaFrequencia(&aux,i,-50);
    printf("%i ,",frequencia[0]);
    while (aux.array[i]!=';') {
            i++;
        }
    while (j<256 && i<(aux.used-1)){
        frequencia[j]=calculaFrequencia(&aux,i, frequencia[j-1]);
        printf("%i ,", frequencia[j]);
         i++;
        while (aux.array[i]!=';') {
            i++;
        }
        j++;
    } 
    printf("\n%i",aux.used);
    //printf ("\n %i",frequencia[5]);
 }


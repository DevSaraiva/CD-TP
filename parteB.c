#include <math.h>
#include "buffer.h"


//Função que dado o indice da frequencia num Buffer de chars devolve essa mesma frequência em formato inteiro
 int calculaFrequencia (Buffer *a, int indice, int freq_anterior){
    int i=1, b=0, freq=0;
    while (a->array[indice + i]!=';' && indice + i < a->used){
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
//Função que retira as frequências de um buffer de char e coloca num array para facilitar a análise
 int retiraFreq (Buffer * aux, int * frequencia){
    
    int i = 0, j=1;
       
    frequencia[0]= calculaFrequencia(aux,i,-50);
    while (aux->array[i]!=';') {
            i++;
        }
    while (i < aux -> used){
        
        frequencia[j]=calculaFrequencia(aux,i, frequencia[j-1]);
         i++;

        while (aux->array[i]!=';') {
            i++;
        }
        j++;
    } 
    return 0;
 }

//Função que ordena um array por ordem decrescente
void BubbleSort(int a[], int N)
{
    int i, j, temp;
    for (i = 0; i < (N - 1); ++i)
    {
        for (j = 0; j < N - 1 - i; ++j )
        {
            if (a[j] < a[j+1])
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
}

//Função usada para debugging do código
int print_array(int *array, int length)
{
    for (int i = 0; i < length; i++) { printf("%d ",array[i]);}
    return 0;
}

//Função que dado um Buffer de frequencias produz um buffer codificado por SF
int codificaBuffer(Buffer * initial, Buffer * final){
    
    int bloco = 1;
    Buffer aux;
    initBuffer (&aux, 150);
    copyNelments (initial, &aux, 1, 2+2*bloco);
    int frequencia[aux.elem + 1];
    printBuff(&aux);
    printf("\n");
    retiraFreq(&aux,frequencia);
    print_array(frequencia,aux.elem + 1);
    
    
   
    
    return 0;
}






int main(){
    
    Buffer initial = read_file_buffer(&initial,"aaa.txt.rle.freq");
    Buffer aux;
    initBuffer(&aux, 150);
    copyNelments (&initial, &aux, 1, 2+2*1);
    codificaBuffer(&initial,&aux);
    

    
}
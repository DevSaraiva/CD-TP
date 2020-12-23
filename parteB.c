#include <math.h>
#include "buffer.h"


//Função que dado o indice da frequencia num Buffer de chars devolve essa mesma frequência em formato inteiro
 int calculaFrequencia (Buffer *a, int indice, int freq_anterior){
    int i=1, b=0, freq=0;
    if (indice == (a->used-1)) return freq_anterior;
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
    while (i < aux -> used  ){
        frequencia[j]=calculaFrequencia(aux,i, frequencia[j-1]);
        i++;
        if (i<aux->used-1){
            while (aux->array[i]!=';') {
                i++;
            }
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

//Função que inicializa array de Buffers
int initBufferArray(Buffer array [], int N){
    
    int i = 0;
    while(i <  N){
        initBuffer(&array[i],10);
        i++;
    }
return 0;
}


//Função que calcula a soma das frequências do grupo freq[i,j] (i.e., freq[i]+...+freq[j])
int soma (int freq[],int i,int j){
    int resultado=0;
    while (i<=j){
        resultado += freq[i];
        i++;
    }
    return resultado;
}

int calcula_melhor_divisao (int freq[],int i,int j){
    int div = i;
    int total , mindif , dif , g1, g2;
    total = mindif = dif = soma(freq,i,j);
    while (dif == mindif){
        g1 = soma(freq,i,div);   
        g2 = total - g1;
        dif = abs(g1-g2);
        if (dif < mindif){
             div = div +1;
            mindif = dif;
        }
        else dif = mindif + 1;
        }
    return div-1;
}

void add_bit_to_code(char c, Buffer codes[],int start,int end){
    int i = start;
    while(i <= end){
        insertBuffer(&codes[i], c);
        i++;
    }
    
}

//
void calcular_codigos_SF(int freqs[],Buffer codes[],int start, int end){
    
    int div;

    if (start!=end){
        div = calcula_melhor_divisao(freqs,start,end);
        add_bit_to_code('0',codes,start,div);
        add_bit_to_code('1',codes,div+1,end);
        calcular_codigos_SF(freqs,codes,start,div);
        calcular_codigos_SF(freqs,codes,div+1,end);
    }
}

//Função que calcula o numero de frequencias diferentes de 0
int calcula_n_freq (int freq[]){
    int i=0;
    while (freq[i]!=0){
        i++;
    }
    return i;
}

//Função que dado um Buffer de frequencias produz um buffer codificado por SF
int codificaBuffer(Buffer * initial, Buffer * final){
    
    int i = 0;
    int bloco = 1;
    Buffer aux;
    initBuffer (&aux, 150);
    copyNelments (initial, &aux, 1, 2+2*bloco);
    int tam_freq = aux.elem + 1;
    int frequencia[tam_freq];
    retiraFreq(&aux,frequencia);
    BubbleSort(frequencia,tam_freq);
    int n_freq_n0  = calcula_n_freq (frequencia); 
    printf("%i\n",n_freq_n0);
    Buffer codes[tam_freq];
    initBufferArray(codes, tam_freq);
    calcular_codigos_SF(frequencia,codes,0,15);
    print_array(frequencia,tam_freq);
    while(i < 10){
        printBuff(&codes[i]);
        printf("\n");
        i++;
    } 
    return 0;
}


int main(){
    
    Buffer initial = read_file_buffer(&initial,"aaa.txt.rle.freq");
    Buffer aux;
    initBuffer(&aux, 150);
    codificaBuffer(&initial,&aux);
    
}

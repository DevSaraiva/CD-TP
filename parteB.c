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

// Função que dado um array de frequências  calcula a melhor divisão de modo a formar 2 blocos cuja soma das frequências seja o mais identico possível 

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

// Função que adiciona o bit "0" ou o bit "1" a uma string correspondente a determinada frquência

void add_bit_to_code(char c, Buffer codes[],int start,int end){
    int i = start;
    while(i <= end){
        insertBuffer(&codes[i], c);
        i++;
    }
    
}
// Função que calcula os códigos SF com base na melhor divisão possível 

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

//Função que copia array para outro array

int copy_array(int a[], int b[], int len){
    int i = 0;
    while ( i < len){
        b[i] = a[i];
        i++;
    }
    
    return 0;
}


//Função que calcula o indice do ultimo elemento não nulo 

int calcula_i_freq (int freq[]){
    int i=0;
    while (freq[i]!=0){
        i++;
    }
    return i ;
}

// Função que copia a codes para o final buffer

int copyCodetoBufer(Buffer * codes, Buffer * final){
    
    int tam = codes->used;
    int i = 0;
    char c;
    while(i < tam){
        c = codes -> array[i];
        insertBuffer(final, c);
        i++;
    }

    
}

//Função que calcula o número de blocos

int blockNumber (Buffer * initial){

    int number;
    number = initial -> array[3];

    return number - 48;

}

// Função que encontra o indice de determinado elemento

int findIndex(int freq, int sorted[]){
    int i = 0;
    while(freq != sorted[i]){
        i++;
    }

    sorted[i] = -1;
return i;
}

void printCodesArray( Buffer codes[], int N){
    int i = 0;
    while(i < N){
        printBuff(&codes[i]);
        printf("  ");
        i++;
    }
}

// Função que codifica bloco

void codeBlock(Buffer * aux, Buffer * final, int bloco){

    int i = 0;
    int freq;
    int index;
    
    // Retira  as frequências de determinado bloco e organiza-as por ordem decrescente
    int tam_freq = aux -> elem + 1;
    int frequencias[tam_freq];
    int frequenciaSorted[tam_freq];
    retiraFreq(aux,frequencias);
    copy_array(frequencias,frequenciaSorted, tam_freq);
    BubbleSort(frequenciaSorted,tam_freq);
    int n_freq_n0  = calcula_i_freq (frequenciaSorted); 
    
    // Cria o buffer com a codificação dos vários simbolos
    Buffer codes[n_freq_n0];
    initBufferArray(codes, n_freq_n0);
    calcular_codigos_SF(frequenciaSorted,codes,0,n_freq_n0 - 1);
 
    // Copia frequencias
    insertBuffer(final,'@');
    while(i < tam_freq){
        
        freq = frequencias[i];
        if ( freq != 0){
        index = findIndex(freq, frequenciaSorted);
        copyCodetoBufer(&codes[index],final);}
       
        if(i + 1 < tam_freq)insertBuffer(final,';');

        i++;
    }
}



//Função que dado um Buffer de frequencias produz um buffer codificado por SF

void code(Buffer * initial, Buffer * final){
    
    copyNelments(initial,final,2,0);
    
    int bloco = 1;
    int blocks = blockNumber(initial);
    
    
    while(bloco <= blocks){
        Buffer aux;
        initBuffer (&aux, 150);
        copyNelments (initial, &aux, 1, 2+2*bloco);
        copyNelments(initial,final,1,2*bloco + 1); // copia tamanaho do  bloco 
        codeBlock(&aux, final, bloco);
        freeBuffer(&aux);
        bloco++;}
    
    
    insertBuffer(final,'@');
    insertBuffer(final,'0');
   
    
}


int main(){
    
    char name[] = "aaa.txt.freq";
    Buffer initial = read_file_buffer(&initial,name);
    Buffer final;
    initBuffer(&final, 150);
    code(&initial,&final);
    write_file_buffer(&final,name);
    
}

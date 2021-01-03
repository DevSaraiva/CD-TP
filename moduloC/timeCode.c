#include <stdio.h> 
#include <unistd.h>
#include <time.h>
#include "fileOpener.c"
#include "filetxt.c"
#include "contador.c"

int tempoExecucao()
{ 
    clock_t start = clock();
    contSimbSep();
    abrirFicheiro();
    openFile();  //funcao para abrir o ficheiro 
    clock_t end = clock(); 
    double time_taken = (double)(end - start)/CLOCKS_PER_SEC; // in seconds 

    printf("tempo de execucao do modulo: %f\n", time_taken); 
    return 0; 
}

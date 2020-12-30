#include <stdio.h> 
#include <unistd.h>
#include <time.h>
#include "fileOpener.c"

int tempoExecucao() 
{ 
    clock_t start = clock();
    openFile();     
    sleep(0);
    clock_t end = clock(); 
    double time_taken = (double)(end - start)/CLOCKS_PER_SEC; // in seconds 

    printf("time program took %f seconds to execute \n", time_taken); 
    return 0; 
}
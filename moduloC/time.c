#include <stdio.h>
#include <time.h>

int data()
{
  time_t t = time(NULL);
  struct tm tm = *localtime(&t);
  printf("\n Andre Presa, A82917, MIEI/CD, %d-%02d-%02d", tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900);
  printf("\n Modulo: c (codificacaoo dum ficheiro de simbolos)");
}
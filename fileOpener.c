#include <stdio.h>  

void openFile(){  
   FILE *fp;  
   fp = fopen("aaa.txt.rle.shaf", "rb");//opening file  
   //fprintf(fp, "Hello file by fprintf...\n");//writing data into file  
   fclose(fp);//closing file  
}


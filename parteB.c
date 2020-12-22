#include "buffer.h"




int main(){
   Buffer initial_buffer = read_file_buffer(&initial_buffer,"aaa.txt.rle.freq");
   Buffer final_buffer;
   initBuffer(&final_buffer,150);
   copyNelments(&initial_buffer, &final_buffer,2,0);
   printBuff(&final_buffer);

   
   
    
    
    return 0;
}


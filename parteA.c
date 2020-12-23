#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_RLEN 255
 
/* Returns the Run Length Encoded string for the 
   source string src */
char* encode(char* src)
{
    int rLen;                // numero de repeticoes
    char count[MAX_RLEN];    // buffer que guarda nº repeticoes
    int len = strlen(src);   // src = string original; len é o length da string original.
    char* dest = (char*)malloc(sizeof(char) * (len * 2 + 1));          //dest é a string final (comprimida)
 
    int i, j = 0, k;
 
    /* atravessar a string original um a um */
    for (i = 0; i < len; i++) {                           
        
        dest[j++] = src[i];                                   
        rLen = 1;                                       

        while (i + 1 < len && src[i] == src[i + 1]) {
            rLen++;
            i++;
        }

        if(rLen == 3) { 
            /*for(int n = rLen; n >= 1;n--){
                //sprintf(count,"%c",src[i]);
        
        }*/
        sprintf(count,"%c%c",src[i],src[i]);
        }
        
        else if(rLen == 2) {
            sprintf(count,"%c",src[i]);

        } 
        else if(rLen == 1){
            sprintf(count,"",src[i]);
        }
        else {
            sprintf(count, "{%d}₁", rLen);               
        }
        
        
        for (k = 0; *(count + k); k++, j++) {

            dest[j] = count[k];
        }
    }
    dest[j] = '\0';
    return dest;
}

int main()
{
    char str[] = "aaaaaappppppp";
    char* res = encode(str);
    printf("%s", res);
    getchar();
}



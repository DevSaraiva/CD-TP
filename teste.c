#include <stdio.h>

int main(){
    char n;
    char charizard[] = "{0}₁a{4}₁g";
    int i = 0;
    printf("%c", charizard[i]);
    i += 6;
    printf("%c", charizard[i]);
    i+= 7;
    printf("%c", charizard[i]);
    i+=13;
    printf("%c", charizard[i]);


    return 0;
}
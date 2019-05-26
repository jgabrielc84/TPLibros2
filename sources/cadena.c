#include "../headers/cadena.h"

void discardChars(){
    char c;
    while((c = getchar()) != '\n' && c != EOF);
    return;
}

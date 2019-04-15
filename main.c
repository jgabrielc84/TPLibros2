#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consola.h"
#include "libro.h"



int main()
{
    FILE *fa = NULL;
    if ((fa=fopen("libros", "ab+"))==NULL){
        exit(EXIT_FAILURE);
    }
    FILE *f = NULL;
    if ((f=fopen("libros", "rb+"))==NULL){
        exit(EXIT_FAILURE);
    }


    iniciarConsola(f);

    fclose(f);
    fclose(fa);
    return 0;
}

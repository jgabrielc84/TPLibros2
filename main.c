#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consola.h"
#include "libro.h"



int main()
{
    FILE *f = NULL;
    if ((f=fopen("libros", "ab+"))==NULL){
        exit(EXIT_FAILURE);
    }


    iniciarConsola(f);

    fclose(f);
    return 0;
}

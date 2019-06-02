#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "consola.h"
#include "libro.h"



int main()
{
    //Abrimos nuestro archivo.
    FILE *ptrArchivo = NULL;
    if ((ptrArchivo=fopen("libros", "rb+"))==NULL){
        exit(EXIT_FAILURE);
    }
    //Iniciamos la consola.
    iniciarConsola(ptrArchivo);
    //Cerramos el archivo.
    fclose(ptrArchivo);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include "consola.h"
#include "lista.h"

int main()
{
    //Abrimos el archivo.
    FILE* ptrArchivo = fopen("libros", "rb+");
    if(ptrArchivo == NULL){
        printf("El archio 'libros' no pudo abrirse correctamente.");
        exit(EXIT_FAILURE);
    }
    //Inicializamos la lista de retiro en sucursal.
    ST_LISTA_VENTAS* listaRetirosEnSucursal = NULL;
    //Inicializamos la cola de envios a domicilio
    ST_COLA_LIBROS colaEnviosADomicilio;
    (&colaEnviosADomicilio)->inicio = NULL;
    (&colaEnviosADomicilio)->fin = NULL;
    //Iniciamos la consola.
    iniciarConsola(ptrArchivo, &listaRetirosEnSucursal, &colaEnviosADomicilio);
    //Cerramos el archivo.
    fclose(ptrArchivo);
    return 0;
}

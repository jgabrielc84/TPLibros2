#ifndef CONSOLA_H_INCLUDED
#define CONSOLA_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "libro.h"
#include "lista.h"

void iniciarConsola (FILE* ptrArchivo, ST_LISTA_VENTAS** listaRetirosEnSucursal, ST_COLA_LIBROS* colaEnviosADomicilio);
void gestionarLibroConsola(ST_LIBRO libro, FILE* ptrArchivo);
#endif // CONSOLA_H_INCLUDED

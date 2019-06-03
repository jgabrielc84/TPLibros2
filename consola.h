#ifndef CONSOLA_H_INCLUDED
#define CONSOLA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "lista.h"

void iniciarConsola (FILE* ptrArchivo);
void gestionConsola (FILE* ptrArchivo);
void ventaConsola(FILE* ptrArchivo, ST_NODO* listaDeVenta);
#endif // CONSOLA_H_INCLUDED

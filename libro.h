#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char nombre[20];
    char apellido[20];
}ST_AUTOR;

typedef struct{
    char titulo[50];
    ST_AUTOR autor;
    double precio;
    char ISBN[10];
    int stockDisponible;
    int stockReservado;
}ST_LIBRO;

int contarLibros (FILE*f);
void crearLibroPorConsola(FILE *f);
void listarLibros(FILE*f);
int buscarLibroPorISBN (FILE*f);


#endif // LIBRO_H_INCLUDED

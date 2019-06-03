#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

ST_LIBRO buscarLibroIesimo(int i, FILE* ptrArchivo);
int contarLibros(FILE* ptrArchivo);
void crearLibroPorConsola(FILE* ptrArchivo);
void listarLibros(FILE* ptrArchivo);
int buscarLibroPorISBNPorConsola(FILE* ptrArchivo);
//void abrirLibro (FILE* nombrePtr, const char* nombreArchivo, const char* tipoApertura);
int buscarLibroPorAutorOTituloPorConsola(FILE* ptrArchivo);

#endif // LIBRO_H_INCLUDED

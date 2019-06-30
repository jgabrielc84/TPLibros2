#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define lenNombre 20
#define lenTitulo 50
#define lenISBN 10

typedef struct{
    char nombre[lenNombre];
    char apellido[lenNombre];
}ST_AUTOR;

typedef struct{
    char titulo[lenTitulo];
    ST_AUTOR autor;
    double precio;
    char ISBN[lenISBN];
    int stockDisponible;
    int stockReservado;
}ST_LIBRO;

void actualizarStockReservadoPorISBN(FILE* ptrArchivo, char ISBN[lenISBN], int cant);
void actualizarStockDisponiblePorISBN(FILE* ptrArchivo, char ISBN[lenISBN], int cant);
void actualizarLibroEnArchivo(ST_LIBRO libro, FILE* ptrArchivo);
void mostrarLibro(ST_LIBRO libro);
void actualizarStockPorISBN(FILE* ptrArchivo, char ISBN[lenISBN]);
void crearLibro(FILE* ptrArchivo);
ST_LIBRO buscarLibroPorISBNPorConsola(FILE* ptrArchivo);
ST_LIBRO buscarLibroPorAutorOTituloPorConsola(FILE* ptrArchivo);
void editarLibro(ST_LIBRO libro, FILE* ptrArchivo);
void eliminarLibro(ST_LIBRO libro, FILE* ptrArchivo);
void listarLibros(FILE* ptrArchivo);
ST_LIBRO inicializarLibro();
#endif // LIBRO_H_INCLUDED

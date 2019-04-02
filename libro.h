#ifndef LIBRO_H_INCLUDED
#define LIBRO_H_INCLUDED
#include "string.h"
#define cant_lib 50
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

void inicializar (ST_LIBRO);

//ST_LIBRO crearLibro(const char *titulo, const ST_AUTOR autor, const double precio, const char *ISBN, int stockDisponible, int stockReservado);
void crearLibro(const char *titulo, const ST_AUTOR autor, const double precio, const char *ISBN, int stockDisponible, int stockReservado, ST_LIBRO libros[]);
void crearLibroPorConsola(ST_LIBRO libros[]);

ST_AUTOR crearAutor(const char *nombre, const char *apellido);


#endif // LIBRO_H_INCLUDED

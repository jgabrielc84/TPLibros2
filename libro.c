#include "libro.h"



void crearLibro(const char *titulo, const ST_AUTOR autor, const double precio, const char *ISBN, int stockDisponible, int stockReservado, ST_LIBRO libros[]){
    for(int i = 0; i < CANT_LIBROS; i++){
            //cambiar a usar cadena.h
        if(strcmp(libros[i].ISBN, "") == 0){//*libros[i].ISBN == '\0'){
            strcpy(libros[i].titulo, titulo);
            libros[i].autor = autor;
            libros[i].precio = precio;
            strcpy(libros[i].ISBN, ISBN);
            libros[i].stockDisponible = stockDisponible;
            libros[i].stockReservado = stockReservado;
            return;
        }
    }
}


ST_AUTOR crearAutor(const char *nombre, const char *apellido){
    ST_AUTOR autor;
    strcpy(autor.apellido, apellido);
    strcpy(autor.nombre, nombre);
    return autor;
}


void inicializarLibros(ST_LIBRO libros[], int N){
    for (int i=0; i<N; i++){
        strcpy(libros[i].titulo, "");
        libros[i].autor = crearAutor("","");
        libros[i].precio = 0;
        strcpy(libros[i].ISBN, "");
        libros[i].stockDisponible = 0;
        libros[i].stockReservado = 0;
    }
}

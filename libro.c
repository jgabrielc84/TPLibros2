#include "libro.h"

void crearLibroPorConsola(ST_LIBRO libros[]){
    char titulo[50];
    double precio;
    char ISBN[10];
    int stockDisponible;
    int stockReservado;
    char nombreAutor[50];
    char apellidoAutor[50];
    printf("Ingresar el ISBN del libro\n");
    scanf("%s", ISBN);
    printf("Ingresar el titulo del libro\n");
    scanf(" %[^\t\n]s", titulo);
    printf("Ingresar el nombre del autor del libro\n");
    scanf(" %[^\t\n]s", nombreAutor);
    printf("Ingresar el apellido del autor del libro\n");
    scanf(" %[^\t\n]s", apellidoAutor);
    printf("Ingresar el precio del libro\n");
    scanf("%lf", &precio);
    printf("Ingresar el stock disponible\n");
    scanf("%d", &stockDisponible);
    printf("Ingresar el stock reservado\n");
    scanf("%d", &stockReservado);
    crearLibro(titulo, crearAutor(nombreAutor, apellidoAutor), precio, ISBN, stockDisponible, stockReservado, libros);
}

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

void inicializarLibros (ST_LIBRO libros[], int N) {
    for (int i=0; i<N; i++){
        strcpy(libros[i].titulo, "");
        libros[i].autor = crearAutor("","");
        libros[i].precio = 0;
        strcpy(libros[i].ISBN, "");
        libros[i].stockDisponible = 0;
        libros[i].stockReservado = 0;
    }
}

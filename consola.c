#include "consola.h"
#include "libro.h"
#include <stdio.h>

int buscarPorISBN (const char *ISBN, ST_LIBRO libros [] ) {
    int i = 0;
    while(strcmp(libros[i].ISBN, "") != 0){
        if (strcmp(ISBN, libros[i].ISBN) == 0 ){
            return i;
        }
        i++;
    }
    return -1;//Error
}

//Despues modificar de a uno
void editarLibros(ST_LIBRO libros []){
    char cadena [10];
    const char titulo[50];
    double precio;
    char ISBN[10];
    int stockDisponible;
    int stockReservado;
    char nombreAutor[50];
    char apellidoAutor[50];
    printf("Ingresar el ISBN: ");
    scanf("%s", cadena);
    int pos = buscarPorISBN(cadena, libros);
    printf("Titulo: %s\n", libros[pos].titulo);
    scanf("%[^\t\n]s", titulo);
    strcpy(libros[pos].titulo, titulo);
    printf("%s\n", libros[pos].autor.apellido);
    scanf("%[^\t\n]s", apellidoAutor);
    strcpy(libros[pos].autor.apellido, apellidoAutor);
    printf("%s\n", libros[pos].autor.nombre);
    scanf(" %[^\t\n]s", nombreAutor);
    strcpy(libros[pos].autor.nombre, nombreAutor);
    printf("%5.2lf\n", libros[pos].precio);
    scanf(" %lf", &precio);
    libros[pos].precio = precio;
    printf("%i\n", libros[pos].stockDisponible);
    scanf(" %i", &stockDisponible);
    libros[pos].stockDisponible = stockDisponible;
    printf("%i\n", libros[pos].stockReservado);
    scanf(" %i", &stockReservado);
    libros[pos].stockReservado = stockReservado;
}

void iniciarConsola (ST_LIBRO libros[]){
        int N = -1;
        system("cls");
        printf("Bienvenidos al sistema\n");
        printf("[1] - Gestion de libros\n");
        printf("[2] - Venta de libros\n");
        printf("[3] - Entrega de libros comprados\n");
        scanf("%i", &N);
        switch (N){
            case 1:
                system("cls");
                gestionConsola(libros);
                break;
        }
}

void listarLibros(ST_LIBRO libros[]){
    int i = 0;
    while(strcmp(libros[i].ISBN, "") != 0){
        printf("ISBN: %s Titulo: %s Autor: %s %s Precio: %4.2lf Stock Disponible: %d Stock Reservado %d\n",
               libros[i].ISBN,
               libros[i].titulo,
               libros[i].autor.apellido,
               libros[i].autor.nombre,
               libros[i].precio,
               libros[i].stockDisponible,
               libros[i].stockReservado);
        i++;
    }
}

void gestionConsola (ST_LIBRO libros[]){
        int N = -1;
        printf("\n[1] - Crear libro\n");
        printf("[2] - Buscar libro\n");
        printf("[3] - Listar libros\n");
        printf("[4] - Editar libros\n");
        printf("[5] - Eliminar libros\n");
        printf("[0] - Volver\n");
        scanf("%d", &N);
        switch (N){
        case 1:
            crearLibroPorConsola(libros);
            gestionConsola(libros);
            break;
        case 3:
            system("cls");
            listarLibros(libros);
            gestionConsola(libros);
            break;
        case 4:
            editarLibros(libros);
            gestionConsola(libros);
            break;
        }
}

#include "consola.h"
#include "libro.h"


void iniciarConsola (FILE*f){
        int N = -1;
        system("cls");
        printf("Bienvenidos al sistema\n");
        printf("Tamaño de ST_LIBRO = %i bytes\n", sizeof(ST_LIBRO)); //Despues borrar
        printf("[1] - Gestion de libros\n");
        printf("[2] - Venta de libros\n");
        printf("[3] - Entrega de libros comprados\n");
        printf("[4] - Salir\n");
        scanf("%i", &N);
        switch (N){
            case 1:
                system("cls");
                gestionConsola(f);
                break;
        }
}

void gestionConsola (FILE *f){
        int N = -1;
        printf("\n[1] - Crear libro\n");
        printf("[2] - Buscar libro\n");
        printf("[3] - Listar libros\n");
        printf("[4] - Volver\n");
        scanf("%d", &N);
        switch (N){
        case 1:
            crearLibroPorConsola(f);
            gestionConsola(f);
            break;
        case 2:
            buscarLibro(f);
            break;
        case 3:
            system("cls");
            listarLibros(f);
            gestionConsola(f);
            break;
        case 4:
            iniciarConsola(f);
            break;
        }
}

void buscarLibro (FILE*f){
        int N = -1;
        system("cls");
        printf("\n[1] - Buscar libro por ISBN\n");
        printf("[2] - Buscar libro por titulo o autor\n");
        printf("[3] - Volver\n");
        scanf("%d", &N);
        int i;
        switch (N){
        case 1:
            i = buscarLibroPorISBN (f);
            mostrarLibroIesimo(i,f);
            gestionarLibro(i,f);
            break;
        case 2:

            break;
        case 3:
            system("cls");
            gestionConsola(f);
            break;
}

}

void gestionarLibro (int i, FILE *f){
        int N = -1;
        printf("\n[1] - Editar libro\n");
        printf("[2] - Eliminar libro\n");
        printf("[3] - Volver\n");
        scanf("%d", &N);
        switch (N){
        case 1:
            break;
        case 2:
            eliminarLibro(i,f);
            break;
        case 3:
            system("cls");
            gestionConsola(f);
            break;
}
}

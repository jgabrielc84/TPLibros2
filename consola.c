#include "consola.h"
#include "libro.h"
#include "lista.h"

void ventaConsola(FILE* ptrArchivo, ST_NODO* listaDeVenta){
    int opcion = -1;
    printf("Venta de libros\n\n");
    printf("[1] - Listar libros\n");
    printf("[2] - Ingresar articulos a venta\n");
    printf("[3] - Confirmar venta\n");
    printf("[4] - Cancelar venta\n");
    printf("[0] - Volver\n\n");
    printf("Opcion: ");
    scanf("%i", &opcion);
    switch(opcion){
    case 1://listar libros
        system("cls");
        listarLibros(ptrArchivo);
        printf("\n");
        ventaConsola(ptrArchivo, listaDeVenta);
        break;
    case 2://Ingresar articulos a venta
        ingresarArticulosAVenta(ptrArchivo, listaDeVenta);
        break;
    case 3://Confirmar venta
        break;
    case 4://Cancelar venta
        break;
    case 0://volver
        iniciarConsola(ptrArchivo);
        break;
    default:
        printf("La opcion seleccionada no corresponde a una opcion del menu.\n");
        printf("Presione una tecla para continuar.\n");
        getch();
        system("cls");
        break;
    }
}

void iniciarConsola(FILE* ptrArchivo){
    int opcion = -1;
    system("cls");
    printf("Bienvenidos al sistema de Ventas \"LIBROS\"\n\n");
    //printf("Tamaño de ST_LIBRO = %i bytes\n", sizeof(ST_LIBRO)); //Despues borrar
    printf("[1] - Gestion de libros\n");
    printf("[2] - Venta de libros\n");
    printf("[3] - Entrega de libros comprados\n");
    printf("[0] - Salir\n\n");
    printf("Opcion: ");
    scanf("%i", &opcion);
    switch (opcion){
        case 1:
            system("cls");
            gestionConsola(ptrArchivo);
            break;
        case 2:
            system("cls");
            ST_NODO* listaDeVenta = NULL;
            ventaConsola(ptrArchivo, listaDeVenta);
            break;
        case 3:
            system("cls");
            //entregaLibrosConsola(ptrArchivo);
            break;
        case 0:
            system("cls");
            printf("Que tenga un buen dia!\n\n");
            printf("Presione una tecla para continuar.\n");
            getch();
            exit(EXIT_SUCCESS);
            break;
    }
}

void gestionConsola(FILE* ptrArchivo){
    int N = -1;
    printf("\n[1] - Crear libro\n");
    printf("[2] - Buscar libro\n");
    printf("[3] - Listar libros\n");
    //printf("[4] - Editar libro\n");
    //printf("[5] - Eliminar libro\n");
    printf("[0] - Volver\n");
    scanf("%d", &N);
    int libroiesimo;
    switch (N){
    case 1://crear libro
        crearLibroPorConsola(ptrArchivo);
        gestionConsola(ptrArchivo);
        break;
    case 2://buscar libro
    case 4:
    case 5:
        system("cls");
        buscarLibro(ptrArchivo);
        break;
    case 3://listar libro
        system("cls");
        listarLibros(ptrArchivo);
        gestionConsola(ptrArchivo);
        break;
    /*case 4://editar libro
        system("cls");
        libroiesimo = buscarLibroPorISBN(ptrArchivo);
        mostrarLibroIesimo(libroiesimo, ptrArchivo);
        editarLibro(libroiesimo, ptrArchivo);
        system("cls");
        gestionConsola(ptrArchivo);
        break;
    case 5://eliminar libro
        system("cls");
        libroiesimo = buscarLibroPorISBN(ptrArchivo);
        mostrarLibroIesimo(libroiesimo, ptrArchivo);
        eliminarLibro(libroiesimo, ptrArchivo);
        system("cls");
        gestionConsola(ptrArchivo);
        break;*/
    case 0://volver
        iniciarConsola(ptrArchivo);
        break;
    }
}

void buscarLibro (FILE* ptrArchivo){
    int N = -1;
    printf("\n[1] - Buscar libro por ISBN\n");
    printf("[2] - Buscar libro por titulo o autor\n");
    printf("[3] - Volver\n");
    scanf("%d", &N);
    int libroiesimo;
    switch (N){
    case 1://isbn
        system("cls");
        libroiesimo = buscarLibroPorISBNPorConsola(ptrArchivo);
        if(libroiesimo != -1){
            mostrarLibroIesimo(libroiesimo, ptrArchivo);
            gestionarLibro(libroiesimo, ptrArchivo);
        }else{
            printf("Libro no encontrado.");
            system("cls");
            buscarLibro(ptrArchivo);
        }
        break;
    case 2://titulo o autor
        /*system("cls");
        buscarLibroPorTituloOAutor(ptrArchivo);
        seleccionarLibro(ptrArchivo);*/
        libroiesimo = buscarLibroPorAutorOTituloPorConsola(ptrArchivo);
        if(libroiesimo != -1){
            mostrarLibroIesimo(libroiesimo, ptrArchivo);
            gestionarLibro(libroiesimo, ptrArchivo);
        }else{
            printf("Libro no encontrado.");
            buscarLibro(ptrArchivo);
        }
        break;
    case 3://volver
        system("cls");
        gestionConsola(ptrArchivo);
        break;
    }
}

void gestionarLibro(int libroiesimo, FILE* ptrArchivo){
    int N = -1;
    printf("\n[1] - Editar libro\n");
    printf("[2] - Eliminar libro\n");
    printf("[3] - Volver\n");
    scanf("%d", &N);
    switch (N){
    case 1:
        editarLibro(libroiesimo, ptrArchivo);
        system("cls");
        gestionConsola(ptrArchivo);
        break;
    case 2:
        eliminarLibro(libroiesimo, ptrArchivo);
        system("cls");
        gestionConsola(ptrArchivo);
        break;
    case 3:
        system("cls");
        gestionConsola(ptrArchivo);
        break;
    }
}

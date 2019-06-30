#include "libro.h"
#include "consola.h"
#include "venta.h"

void gestionarLibroConsola(ST_LIBRO libro, FILE* ptrArchivo) {
	int opcion = -1;
	while(opcion != 0){
        printf("\n[1] - Editar libro\n");
        printf("[2] - Eliminar libro\n");
        printf("[3] - Buscar otro libro\n");
        printf("[0] - Volver\n");
        scanf("%d", &opcion);
        switch(opcion) {
        case 1:
            editarLibro(libro, ptrArchivo);
            system("cls");
            return;
        case 2:
            eliminarLibro(libro, ptrArchivo);
            system("cls");
            return;
        case 3:
        case 0:
            return;
        }
	}
}

void buscarLibroConsola (FILE* ptrArchivo){
    int opcion = -1;
    ST_LIBRO libro;
    while(opcion != 0){
        libro = inicializarLibro();
        printf("\nInicio -> Gestion -> Buscar Libro\n");
        printf("\n[1] - Buscar libro por ISBN\n");
        printf("[2] - Buscar libro por titulo o autor\n");
        printf("[0] - Volver\n");
        scanf("%d", &opcion);
        switch(opcion){
        case 1://ISBN
            libro = buscarLibroPorISBNPorConsola(ptrArchivo);
            if(strcmp(libro.ISBN, "") != 0){
                mostrarLibro(libro);
                gestionarLibroConsola(libro, ptrArchivo);
            }
            break;
        case 2://titulo o autor
            libro = buscarLibroPorAutorOTituloPorConsola(ptrArchivo);
            if(strcmp(libro.ISBN, "") != 0){
                mostrarLibro(libro);
                gestionarLibroConsola(libro, ptrArchivo);
            }
            break;
        }
    }
}

void gestionConsola(FILE* ptrArchivo){
    int opcion = -1;
    while(opcion != 0){
        printf("\nInicio -> Gestion\n");
        printf("\n[1] - Crear libro\n");
        printf("[2] - Buscar libro\n");
        printf("[3] - Listar libros\n");
        printf("[0] - Volver\n");
        scanf("%d", &opcion);
        switch (opcion){
        case 1://crear libro
            crearLibro(ptrArchivo);
            system("cls");
            break;
        case 2://buscar libro
            system("cls");
            buscarLibroConsola(ptrArchivo);
            system("cls");
            break;
        case 3://listar libro
            system("cls");
            listarLibros(ptrArchivo);
            break;
        }
    }
}
void ventaConsola(FILE* ptrArchivo, ST_LISTA_LIBROS** listaVentas, ST_LISTA_VENTAS** listaRetirosPorSucursal, ST_COLA_LIBROS* colaEnviosADomicilio){
    int opcion = -1;
    int factura = -1;
    while(opcion != 0){
        printf("Inicio -> Ventas\n\n");
        printf("[1] - Listar Libros ingresados a venta\n");
        printf("[2] - Ingresar articulos a venta\n");
        printf("[3] - Finalizar seleccion de libros\n");
        if(*listaVentas == NULL){
            printf("[0] - Volver\n");
        }else{
            printf("[0] - Cancelar venta\n");
        }
        scanf("%d", &opcion);
        switch (opcion){
        case 1://Listar libros
            system("cls");
            printearListaLibros(listaVentas);
            printf("\n");
            break;
        case 2://Ingresar articulos a venta
            system ("cls");
            ingresarArticulosAVenta(ptrArchivo, listaVentas);
            break;
        case 3://Finalizar seleccion de libros
            system ("cls");
            printearListaLibros(listaVentas);
            factura = generarFactura(listaVentas);
            elegirModoDeEntrega(ptrArchivo, factura, listaVentas, listaRetirosPorSucursal, colaEnviosADomicilio);
            break;
        }
    }
}


void enviosADomicilio(FILE* ptrArchivo, ST_LISTA_VENTAS** listaRetirosPorSucursal, ST_COLA_LIBROS* colaEnviosADomicilio) {
	int opcion = -1;
	while(opcion != 0){
        printf("\n[1] - Despachar envios\n");
        printf("[0] - Volver\n");
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            system("cls");
            remover5ElementosDeCola(colaEnviosADomicilio, ptrArchivo);
            system("cls");
            mostrar5ElementosDeCola(colaEnviosADomicilio);
            break;
        }
	}
}

void retirosPorSucursal(FILE* ptrArchivo, ST_LISTA_VENTAS** listaRetirosPorSucursal, ST_COLA_LIBROS* colaEnviosADomicilio) {
	int opcion = -1;
	while(opcion != 0){
        printf("\n[1] - Retirar libros del local\n");
        printf("[0] - Volver\n");
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            system("cls");
            eliminarVentaDeLista(ptrArchivo, listaRetirosPorSucursal);
            system("cls");
            mostrarListaVentas(listaRetirosPorSucursal);
            break;
        }
	}
}

void gestionEntregaDeLibros(FILE* ptrArchivo, ST_LISTA_VENTAS** listaRetirosPorSucursal, ST_COLA_LIBROS* colaEnviosADomicilio) {
	int opcion = -1;
	while(opcion != 0){
        printf("\nInicio -> Despachar Libros\n");
        printf("\n[1] - Mostrar cinco primeros envios a domicilio\n");
        printf("[2] - Mostrar lista de retiro en el local\n");
        printf("[0] - Volver\n");
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            system("cls");
            //si la cola esta vacia, no mostrar nada.
            if(colaEnviosADomicilio->inicio == NULL){
                printf("\nNo hay libros a despachar.\n");
                break;
            }
            mostrar5ElementosDeCola(colaEnviosADomicilio);
            enviosADomicilio(ptrArchivo, listaRetirosPorSucursal, colaEnviosADomicilio);
            break;
        case 2:
            system("cls");
            //si la lista esta vacia, no mostrar nada tampoco
            if(*listaRetirosPorSucursal == NULL){
                printf("\nNo hay libros a retirar.\n");
                break;
            }
            mostrarListaVentas(listaRetirosPorSucursal);
            retirosPorSucursal(ptrArchivo, listaRetirosPorSucursal, colaEnviosADomicilio);
            break;
        }
	}
}



void iniciarConsola (FILE* ptrArchivo, ST_LISTA_VENTAS** listaRetirosEnSucursal, ST_COLA_LIBROS* colaEnviosADomicilio){
    int opcion = -1;
    while(opcion != 0){
        system("cls");
        printf("Bienvenidos al sistema de Ventas \"LIBROS\"\n\n");
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
                ST_LISTA_LIBROS* listaVentas = NULL;
                ventaConsola(ptrArchivo, &listaVentas, listaRetirosEnSucursal, colaEnviosADomicilio);
                break;
            case 3:
                system("cls");
                gestionEntregaDeLibros(ptrArchivo, listaRetirosEnSucursal, colaEnviosADomicilio);
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
}

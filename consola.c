#include "consola.h"
#include "libro.h"


int buscarPorISBN(const char *ISBN, ST_LIBRO libros[]){
    int i = 0;
    while(strcmp(libros[i].ISBN, "") != 0){
        if(strcmp(ISBN, libros[i].ISBN) == 0){
            return i;
        }
        i++;
    }
    return -1;//Error
}

//Despues modificar de a uno
void editarLibros(ST_LIBRO libros[]){
    char cadena[10+1];
    char titulo[50+1];
    char nombreAutor[50];
    char apellidoAutor[50];
    double precio;
    char ISBN[10];
    int stockDisponible;
    int stockReservado;

    printf("\n");
    printf("Ingresar el ISBN a buscar: ");
    scanf("%s", cadena);
    while(getchar()!='\n');// limpia el bufer del teclado

    int pos = buscarPorISBN(cadena, libros);

    printf("\nTitulo: %s\n", libros[pos].titulo);
    printf("Ingrese nuevo titulo: ");
    scanf("%[^\t\n]s", &titulo);
    while(getchar()!='\n');// limpia el bufer del teclado
    strcpy(libros[pos].titulo, &titulo);
    printf("\nTitulo: %s\n", libros[pos].titulo);

    printf("Autor\nApellido: %s\n", libros[pos].autor.apellido);
    printf("Ingrese nuevo apellido: ");
    scanf("%[^\t\n]s", apellidoAutor);
    while(getchar()!='\n');// limpia el bufer del teclado
    strcpy(libros[pos].autor.apellido, &apellidoAutor);
    printf("\nApellido: %s\n", libros[pos].autor.apellido);

    printf("Nombre: %s\n", libros[pos].autor.nombre);
    printf("Ingrese nuevo apellido: ");
    scanf("%[^\t\n]s", nombreAutor);
    while(getchar()!='\n');// limpia el bufer del teclado
    strcpy(libros[pos].autor.nombre, &nombreAutor);
    printf("\nNombre: %s\n", libros[pos].autor.nombre);

    printf("Precio: %5.2lf\n", libros[pos].precio);
    printf("Ingrese nuevo precio: ");
    scanf("%lf", &precio);
    libros[pos].precio = precio;
    printf("\nPrecio: %lf\n", libros[pos].precio);

    printf("Stock disponible: %i\n", libros[pos].stockDisponible);
    printf("Ingrese nuevo stock disponible: ");
    scanf("%i", &stockDisponible);
    libros[pos].stockDisponible = stockDisponible;
    printf("\nStock disponible: %lf\n", libros[pos].stockDisponible);

    printf("Stock reservado: %i\n", libros[pos].stockReservado);
    printf("Ingrese nuevo stock reservado: ");
    scanf("%i", &stockReservado);
    libros[pos].stockReservado = stockReservado;
    printf("\nStock disponible: %lf\n", libros[pos].stockReservado);


    printf("\n");
}

void iniciarConsola(ST_LIBRO libros[]){
        int N = 0;
        system("cls");
        printf("Bienvenidos al sistema\n\n");
        printf("[1] - Gestion de libros\n");
        printf("[2] - Venta de libros\n");
        printf("[3] - Entrega de libros comprados\n\n");
        printf("Opcion: ");
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

void gestionConsola(ST_LIBRO libros[]){
        int N = -1;
        printf("Gestion de libros\n\n");
        printf("[1] - Crear libro\n");
        printf("[2] - Buscar libro\n");
        printf("[3] - Listar libros\n");
        printf("[4] - Editar libros\n");
        printf("[5] - Eliminar libros\n");
        printf("[0] - Volver\n\n");
        printf("Opcion: ");
        scanf("%i", &N);

        switch (N){
        case 1:
            crearLibroPorConsola(libros);
            gestionConsola(libros);
            break;
        case 3:
            system("cls");
            listarLibros(libros);
            printf("\n");
            gestionConsola(libros);
            break;
        case 4:
            editarLibros(libros);
            gestionConsola(libros);
            break;
        }
}

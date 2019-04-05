#include "consola.h"
#include "libro.h"


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
    //char ISBN[10];
    int stockDisponible;
    int stockReservado;

    printf("\n");
    printf("Ingresar el ISBN a buscar: ");
    scanf("%10s", cadena);
    while(getchar()!='\n');// limpia el bufer del teclado

    int pos = buscarPorISBN(cadena, libros);

    printf("\nTitulo: %s\n", libros[pos].titulo);
    printf("Ingrese nuevo titulo: ");
    scanf("%[^\n]50s", titulo);
    while(getchar()!='\n');// limpia el bufer del teclado
    strcpy(libros[pos].titulo, titulo);
    printf("Titulo: %s\n\n", libros[pos].titulo);

    printf("Autor\nApellido: %s\n", libros[pos].autor.apellido);
    printf("Ingrese nuevo apellido: ");
    scanf("%[^\n]50s", apellidoAutor);
    while(getchar()!='\n')// limpia el bufer del teclado
    strcpy(libros[pos].autor.apellido, apellidoAutor);
    printf("Apellido: %s\n", libros[pos].autor.apellido);

    printf("Nombre: %s\n", libros[pos].autor.nombre);
    printf("Ingrese nuevo nombre: ");
    scanf("%[^\n]s", nombreAutor);
    while(getchar()!='\n');// limpia el bufer del teclado
    strcpy(libros[pos].autor.nombre, nombreAutor);
    printf("Nombre: %s\n", libros[pos].autor.nombre);

    printf("Precio: %5.2f\n", libros[pos].precio);
    printf("Ingrese nuevo precio: ");
    scanf("%lf", &precio);
    libros[pos].precio = precio;
    printf("Precio: %f\n", libros[pos].precio);

    printf("Stock disponible: %i\n", libros[pos].stockDisponible);
    printf("Ingrese nuevo stock disponible: ");
    scanf("%i", &stockDisponible);
    libros[pos].stockDisponible = stockDisponible;
    printf("Stock disponible: %i\n", libros[pos].stockDisponible);

    printf("Stock reservado: %i\n", libros[pos].stockReservado);
    printf("Ingrese nuevo stock reservado: ");
    scanf("%i", &stockReservado);
    libros[pos].stockReservado = stockReservado;
    printf("Stock reservado: %i\n", libros[pos].stockReservado);


    printf("\n");
}

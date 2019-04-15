#include "libro.h"

int buscarLibroVacio (FILE*f){
    int cont = -1;
    ST_LIBRO libro;
    fseek(f,0,SEEK_SET);
    while (!feof(f)){
        fread(&libro, sizeof(ST_LIBRO),1,f);
        cont ++;
        if (strcmp(libro.ISBN,"")==0){
            return cont;
            }

            }
    return cont;
}


int contarLibros (FILE*f){
    ST_LIBRO libro;
    int cant = 0;
    fseek(f,0,SEEK_SET);
    while (!feof(f)){
        fread(&libro, sizeof(ST_LIBRO), 1, f);
        cant++;
    }
    return cant;
}

void crearLibroPorConsola(FILE *f){
    int cont = buscarLibroVacio(f);
    ST_LIBRO libro;
    printf("Ingresar el ISBN del libro\n");
    scanf("%s", libro.ISBN);
    printf("Ingresar el titulo del libro\n");
    scanf(" %[^\t\n]s", libro.titulo);
    printf("Ingresar el nombre del autor del libro\n");
    scanf(" %[^\t\n]s", libro.autor.nombre);
    printf("Ingresar el apellido del autor del libro\n");
    scanf(" %[^\t\n]s", libro.autor.apellido);
    printf("Ingresar el precio del libro\n");
    scanf("%lf", &libro.precio);
    printf("Ingresar el stock disponible\n");
    scanf("%d", &libro.stockDisponible);
    printf("Ingresar el stock reservado\n");
    scanf("%d", &libro.stockReservado);
    fseek(f,cont*sizeof(ST_LIBRO),SEEK_SET);
    fwrite(&libro,sizeof(ST_LIBRO),1,f);
}



void listarLibros(FILE*f){
    ST_LIBRO libro;
    fseek(f,0,SEEK_SET);
    while (!feof(f)){
        fread(&libro, sizeof(ST_LIBRO), 1, f);
        mostrarLibro(libro);
    }
}

int buscarLibroPorISBN (FILE*f){
    ST_LIBRO libro;
    char ISBN [10];
    printf("Escriba ISBN \n");
    scanf("%s", ISBN);
    int cont = 0;
    fseek(f,0,SEEK_SET);
    fread(&libro,sizeof(ST_LIBRO),1,f);
    while ((!feof(f))&&(strcmp(ISBN,libro.ISBN)!=0)){
        fread(&libro,sizeof(ST_LIBRO),1,f);
        cont++;
    }
    if (cont>contarLibros(f)){
        return -1;
    }
    return cont;
}

void mostrarLibro (ST_LIBRO libro){
    printf ("ISBN: %s\n", libro.ISBN);
    printf ("Título: %s\n", libro.titulo);
    printf ("Autor: %s %s\n", libro.autor.nombre, libro.autor.apellido);
    printf ("Precio: %4.2f\n", libro.precio);
    printf ("Stock disponible: %i\n", libro.stockDisponible);
    printf ("Stock reservado: %i\n", libro.stockReservado);
}

void mostrarLibroIesimo (int i, FILE *f){
        ST_LIBRO libro;
        fseek(f,i*sizeof(ST_LIBRO),SEEK_SET);
        fread(&libro,sizeof(ST_LIBRO),1,f);
        mostrarLibro(libro);
}

void eliminarLibro (int i, FILE*f){
        ST_LIBRO libro;
        strcpy(libro.ISBN, "");
        strcpy(libro.titulo, "");
        strcpy(libro.autor.apellido, "");
        strcpy(libro.autor.nombre, "");
        libro.precio = 0;
        libro.stockDisponible = 0;
        libro.stockReservado = 0;
        fseek(f,i*sizeof(ST_LIBRO),SEEK_SET);
        fwrite(&libro,sizeof(ST_LIBRO),1,f);
}

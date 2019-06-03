#include "libro.h"
#include "cadena.h"
#include "lista.h"

int buscarLibroPorISBN(FILE* ptrArchivo, char ISBN[]){
    ST_LIBRO libro;
    int cont = 0;
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    while((!feof(ptrArchivo)) && (strcmp(ISBN,libro.ISBN)!= 0)){
        fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
        cont++;
    }
    if(cont > contarLibros(ptrArchivo)){
        return -1;
    }
    return cont;
}

int buscarLibroPorAutorOTituloPorConsola(FILE* ptrArchivo){
    ST_LIBRO libro;
    ST_NODO* lista = NULL;
    char* input = (char*)malloc(sizeof(char) * 50);
    printf("Escriba un Titulo o Autor: ");
    while(getchar() != '\n');
    gets(input);
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    while(!feof(ptrArchivo)){
        if(contieneSubCadena(input, libro.titulo) || contieneSubCadena(input, libro.autor.nombre) || contieneSubCadena(input, libro.autor.apellido)){
            insertarNodo(&lista, libro);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    }
    //printear lista
    ST_NODO* aux = lista;
    if(!aux){
        return -1;
    }
    int n = -1;
    while(aux){
        ++n;
        printf("[%d] %s, %s %s\n", n, aux->libro.titulo, aux->libro.autor.apellido, aux->libro.autor.nombre);
        aux = aux->siguiente;
    }
    printf("\n\nSeleccione un libro: ");
    scanf("%d", &n);
    libro = extraerIesimoNodo(&lista, n);
    return buscarLibroPorISBN(ptrArchivo, libro.ISBN);
}

int buscarLibroVacio(FILE* ptrArchivo){
    int cont = -1;
    ST_LIBRO libro;
    fseek(ptrArchivo, 0, SEEK_SET);
    while(!feof(ptrArchivo)){
        fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
        cont++;
        if(strcmp(libro.ISBN,"") == 0){
            return cont;
        }
    }
    return cont;
}

int contarLibros(FILE*ptrArchivo){
    ST_LIBRO libro;
    int cant = 0;
    fseek(ptrArchivo,0,SEEK_SET);
    while (!feof(ptrArchivo)){
        fread(&libro, sizeof(ST_LIBRO), 1,ptrArchivo);
        cant++;
    }
    return cant;
}

ST_LIBRO crearLibro(){
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
    return libro;
}

void crearLibroPorConsola(FILE* ptrArchivo){
    int cont = buscarLibroVacio(ptrArchivo);
    ST_LIBRO libro;
    libro = crearLibro();
    fseek(ptrArchivo, cont*sizeof(ST_LIBRO), SEEK_SET);
    fwrite(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
}

void mostrarLibro(ST_LIBRO libro){
    printf("\nISBN: %s", libro.ISBN);
    printf("\nTitulo: %s", libro.titulo);
    printf("\nAutor: %s %s", libro.autor.nombre, libro.autor.apellido);
    printf("\nPrecio: %4.2f", libro.precio);
    printf("\nStock disponible: %i", libro.stockDisponible);
    printf("\nStock reservado: %i\n", libro.stockReservado);
}

void listarLibros(FILE* ptrArchivo){
    ST_LIBRO libro;
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    while(!feof(ptrArchivo)){
        if(strcmp(libro.ISBN, "") != 0){
            mostrarLibro(libro);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    }
}

int buscarLibroPorISBNPorConsola(FILE* ptrArchivo){
    char ISBN[10];
    printf("Escriba ISBN \n");
    scanf("%s", ISBN);
    return buscarLibroPorISBN(ptrArchivo, ISBN);
}


ST_LIBRO buscarLibroIesimo(int i, FILE* ptrArchivo){
    ST_LIBRO libro;
    fseek(ptrArchivo, i * sizeof(ST_LIBRO), SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    return libro;
}


void mostrarLibroIesimo(int i, FILE* ptrArchivo){
    ST_LIBRO libro = buscarLibroIesimo(i, ptrArchivo);
    mostrarLibro(libro);
}

void eliminarLibro(int i, FILE* ptrArchivo){
    ST_LIBRO libro;
    strcpy(libro.ISBN, "");
    strcpy(libro.titulo, "");
    strcpy(libro.autor.apellido, "");
    strcpy(libro.autor.nombre, "");
    libro.precio = 0;
    libro.stockDisponible = 0;
    libro.stockReservado = 0;
    printf("¿Esta seguro que desea eliminar el libro? Y/N \n");
    char confirmacion = 'N';
    while(getchar() != '\n');
    scanf ("%c", &confirmacion);
    if((confirmacion == 'Y') || (confirmacion == 'y')){
        fseek(ptrArchivo, i * sizeof(ST_LIBRO), SEEK_SET);
        fwrite(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    }
}

void editarLibro(int libroiesimo, FILE* ptrArchivo){
    fseek(ptrArchivo, libroiesimo * (sizeof(ST_LIBRO)), SEEK_SET);
    printf("Ingrese 0 en caso de no querer cambiar ISBN, titulo o autor \n");
    ST_LIBRO libroNuevo = crearLibro();
    ST_LIBRO libroViejo;
    fread(&libroViejo, sizeof(ST_LIBRO), 1, ptrArchivo);
    if(strcmp(libroNuevo.ISBN, "0") == 0){
        strcpy(libroNuevo.ISBN, libroViejo.ISBN);
    }
    if(strcmp(libroNuevo.titulo, "0") == 0){
        strcpy(libroNuevo.titulo, libroViejo.titulo);
    }
    if(strcmp(libroNuevo.autor.nombre, "0") == 0){
        strcpy(libroNuevo.autor.nombre, libroViejo.autor.nombre);
    }
    if(strcmp(libroNuevo.autor.apellido, "0") == 0){
        strcpy(libroNuevo.autor.apellido, libroViejo.autor.apellido);
    }
    if(libroNuevo.precio == 0){
        libroNuevo.precio = libroViejo.precio;
    }
    printf("Libro nuevo:\n");
    mostrarLibro(libroNuevo);
    printf("\nLibro actual:\n");
    mostrarLibro(libroViejo);
    printf("¿Esta seguro que desea realizar los cambios? Y/N \n");
    char confirmacion = 'N';
    while (getchar()!='\n');
    scanf("%c", &confirmacion);
    if ((confirmacion == 'Y') || (confirmacion == 'y')){
        fseek(ptrArchivo, libroiesimo * (sizeof(ST_LIBRO)), SEEK_SET);
        fwrite(&libroNuevo, sizeof(ST_LIBRO), 1, ptrArchivo);
    }
}

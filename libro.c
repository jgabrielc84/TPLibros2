#include "libro.h"
#include "consola.h"
#include "lista.h"
#include "cadena.h"


ST_LIBRO buscarLibroPorAutorOTituloPorConsola(FILE* ptrArchivo){
    ST_LIBRO libro;
    ST_LISTA_LIBROS* lista = NULL;
    char* input = (char*)malloc(sizeof(char) * lenTitulo);
    printf("Escriba un Titulo o Autor: ");
    while(getchar() != '\n');
    gets(input);
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    while(!feof(ptrArchivo)){
        if(contieneSubCadena(input, libro.titulo) || contieneSubCadena(input, libro.autor.nombre) || contieneSubCadena(input, libro.autor.apellido)){
            agregarLibroALista(&lista, libro);
        }
        fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    }
    //printear lista
    ST_LISTA_LIBROS* aux = lista;
    //si la lista esta vacia, error y retornar
    if(!aux){
        printf("No se ha encontrado ningun libro.\n");
        return libro = inicializarLibro();
    }
    int n = -1;
    //Si hay mas de 1 libro, dejar elegir al usuario
    if(aux && aux->ste){
        while(aux){
            ++n;
            printf("[%d] %s, %s %s\n", n, aux->libro.titulo, aux->libro.autor.nombre, aux->libro.autor.apellido);
            aux = aux->ste;
        }
        printf("\n\nSeleccione un libro: ");
        scanf("%d", &n);
    }else{
        //si hay 1 solo, mostrar ese libro unicamente.
        n = 0;
    }
    libro = extraerLibroEnPosicion(n, &lista);
    return libro;
}

ST_LIBRO inicializarLibro(){
    ST_LIBRO libro;
    strcpy(libro.ISBN, "");
    strcpy(libro.autor.apellido, "");
    strcpy(libro.autor.nombre, "");
    libro.precio = 0.0f;
    libro.stockDisponible = 0;
    libro.stockReservado = 0;
    strcpy(libro.titulo, "");
    return libro;
}

ST_LIBRO buscarLibroPorISBN(FILE* ptrArchivo, char ISBN[lenISBN]){
    ST_LIBRO libro;
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
    bool encontrado = false;
    while(!feof(ptrArchivo) && !encontrado){
        if(strcmp(ISBN, libro.ISBN) == 0){
            encontrado = true;
        }else{
            fread(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
        }
    }
    if(!encontrado){
        libro = inicializarLibro();
    }
    return libro;
}

void actualizarStockDisponiblePorISBN(FILE* ptrArchivo, char ISBN[lenISBN], int cant){
    ST_LIBRO libro = buscarLibroPorISBN(ptrArchivo, ISBN);
    libro.stockDisponible += cant;
    actualizarLibroEnArchivo(libro, ptrArchivo);
}

void actualizarStockReservadoPorISBN(FILE* ptrArchivo, char ISBN[lenISBN], int cant){
    ST_LIBRO libro = buscarLibroPorISBN(ptrArchivo, ISBN);
    libro.stockReservado += cant;
    actualizarLibroEnArchivo(libro, ptrArchivo);
}

void mostrarLibro(ST_LIBRO libro){
    printf("\nISBN: %s", libro.ISBN);
    printf("\nTitulo: %s", libro.titulo);
    printf("\nAutor: %s %s", libro.autor.nombre, libro.autor.apellido);
    printf("\nPrecio: %4.2f", libro.precio);
    printf("\nStock disponible: %i", libro.stockDisponible);
    printf("\nStock reservado: %i\n", libro.stockReservado);
}

ST_LIBRO buscarLibroPorISBNPorConsola(FILE* ptrArchivo){
    char ISBN[lenISBN];
    printf("Escriba ISBN \n");
    scanf("%s", ISBN);
    ST_LIBRO libro = buscarLibroPorISBN(ptrArchivo, ISBN);
    //si el libro no es valido, printear leyenda de error e inicializar libro.
    if(strcmp(libro.ISBN, "") == 0){
        printf("Error. Libro no encontrado.");
        libro = inicializarLibro();
    }
    return libro;
}

ST_LIBRO generarLibroPorConsola(){
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
    libro.stockReservado = 0;
    return libro;
}

void actualizarLibroEnArchivo(ST_LIBRO libro, FILE* ptrArchivo){
    ST_LIBRO auxLibro;
    fseek(ptrArchivo, 0, SEEK_SET);
    fread(&auxLibro, sizeof(ST_LIBRO), 1, ptrArchivo);
    bool cambios = false;
    while(!feof(ptrArchivo) && !cambios){
        //Si encontro nuestro libro a reemplazar (por ISBN)
        if(strcmp(auxLibro.ISBN, libro.ISBN) == 0){
            //ir para atras ST_LIBRO bytes
            fseek(ptrArchivo, -sizeof(ST_LIBRO), SEEK_CUR);
            //escribir nuevo libro
            fwrite(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
            //corte de control
            cambios = true;
        }else{
            fread(&auxLibro, sizeof(ST_LIBRO), 1, ptrArchivo);
        }
    }
}

void editarLibro(ST_LIBRO libroViejo, FILE* ptrArchivo){
    //No editar libros no validos
    if(strcmp(libroViejo.ISBN, "") == 0){
        return;
    }
    printf("Ingrese -1 en caso de no querer cambiar algun dato.\n");
    ST_LIBRO libroNuevo = generarLibroPorConsola();
    if(strcmp(libroNuevo.ISBN, "-1") == 0){
        strcpy(libroNuevo.ISBN, libroViejo.ISBN);
    }
    if (strcmp(libroNuevo.titulo, "-1") == 0) {
        strcpy(libroNuevo.titulo, libroViejo.titulo);
    }
    if (strcmp(libroNuevo.autor.nombre, "-1") == 0) {
        strcpy(libroNuevo.autor.nombre, libroViejo.autor.nombre);
    }
    if (strcmp(libroNuevo.autor.apellido, "-1") == 0) {
        strcpy(libroNuevo.autor.apellido, libroViejo.autor.apellido);
    }
    if (libroNuevo.precio == -1) {
        libroNuevo.precio = libroViejo.precio;
    }
    if(libroNuevo.stockDisponible == -1){
        libroNuevo.stockDisponible = libroViejo.stockDisponible;
    }
    //el stock reservado no cambia
    libroNuevo.stockReservado = libroViejo.stockReservado;

    printf("Libro nuevo:\n");
    mostrarLibro(libroNuevo);
    printf("\nLibro actual:\n");
    mostrarLibro(libroViejo);
    printf("¿Esta seguro que desea realizar los cambios? Y/N \n");
    char confirmacion = 'N';
    while (getchar() != '\n');
    scanf("%c", &confirmacion);
    if ((confirmacion == 'Y') || (confirmacion == 'y')) {
        actualizarLibroEnArchivo(libroNuevo, ptrArchivo);
    }
}

void eliminarLibro(ST_LIBRO libro, FILE* ptrArchivo){
    ST_LIBRO auxLibro;
    char confirmacion = 'N';
    while (getchar() != '\n');
    printf("¿Esta seguro que desea eliminar el libro? Y/N \n");
    scanf("%c", &confirmacion);
    if ((confirmacion == 'Y') || (confirmacion == 'y')) {
        fseek(ptrArchivo, 0, SEEK_SET);
        fread(&auxLibro, sizeof(ST_LIBRO), 1, ptrArchivo);
        bool cambios = false;
        while(!feof(ptrArchivo) && !cambios){
            //Si encontro nuestro libro a reemplazar (por ISBN)
            if(strcmp(auxLibro.ISBN, libro.ISBN) == 0){
                //ir para atras ST_LIBRO bytes
                fseek(ptrArchivo, -sizeof(ST_LIBRO), SEEK_CUR);
                //inicializar libro
                auxLibro = inicializarLibro();
                //escribir nuevo libro
                fwrite(&auxLibro, sizeof(ST_LIBRO), 1, ptrArchivo);
                //corte de control
                cambios = true;
            }
            fread(&auxLibro, sizeof(ST_LIBRO), 1, ptrArchivo);
        }
    }
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

void crearLibro(FILE* ptrArchivo){
    int cont = buscarLibroVacio(ptrArchivo);
    ST_LIBRO libro = generarLibroPorConsola();
    fseek(ptrArchivo, cont * sizeof(ST_LIBRO), SEEK_SET);
    fwrite(&libro, sizeof(ST_LIBRO), 1, ptrArchivo);
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

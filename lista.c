#include "libro.h"
#include "lista.h"

void vaciarListaLibros(ST_LISTA_LIBROS** lista){
    ST_LISTA_LIBROS* aux;
    while(*lista){
        aux = *lista;
        *lista = (*lista)->ste;
        free(aux);
    }
}

ST_LISTA_LIBROS* crearNodoLista() {
	ST_LISTA_LIBROS* nodo = (ST_LISTA_LIBROS*)malloc(sizeof(ST_LISTA_LIBROS));
	nodo->libro = inicializarLibro();
	nodo->ste = NULL;
	return nodo;
}

void agregarLibroALista(ST_LISTA_LIBROS** lista, ST_LIBRO libro){
    ST_LISTA_LIBROS* nodo = crearNodoLista();
    nodo->ste = *lista;
    nodo->libro = libro;
    *lista = nodo;
}

ST_LIBRO extraerLibroEnPosicion(int pos, ST_LISTA_LIBROS** lista){
    ST_LISTA_LIBROS* aux = *lista;
    for(int i = 0; i < pos; i++){
        aux = aux->ste;
    }
    ST_LIBRO libro = (*aux).libro;
    return libro;
}

void printearListaLibros(ST_LISTA_LIBROS** lista){
    ST_LISTA_LIBROS* aux = *lista;
    while(aux){
        mostrarLibro(aux->libro);
        aux = aux->ste;
    }
}

ST_LISTA_VENTAS* crearNodoVentas (int factura, ST_LISTA_LIBROS ** listaLibros){
    //creamos un nuevo nodo
    ST_LISTA_VENTAS* nodoVentas = (ST_LISTA_VENTAS*)malloc(sizeof(ST_LISTA_VENTAS));
    nodoVentas ->IDFactura = factura;
    int cantLibros = 0;
    double precioTotal = 0;
    nodoVentas->listaLibro = *listaLibros;
    nodoVentas->ste = NULL;
    //le insertamos nuestras ventas a este nodo
    ST_LISTA_LIBROS * aux = *listaLibros;
    if (aux!=NULL){
        cantLibros++;
        precioTotal = precioTotal + aux->libro.precio;
    }
    while ((aux!=NULL)&&(aux->ste!=NULL)){
        aux = aux->ste;
        precioTotal = precioTotal + aux->libro.precio;
        cantLibros++;
    }
    nodoVentas->cantLibros = cantLibros;
    nodoVentas->precioTotal = precioTotal;
    return nodoVentas;
}

void agregarVentaACola (int factura, ST_LISTA_LIBROS ** listaVenta, ST_COLA_LIBROS * colaVentas){
    ST_LISTA_VENTAS * nodo = crearNodoVentas(factura, listaVenta);
    if (colaVentas->inicio == NULL){
        colaVentas->inicio = nodo;
    }
    else{
        colaVentas->fin->ste = nodo;
    }
    colaVentas->fin = nodo;
}

void agregarVentaALista (int factura, ST_LISTA_LIBROS ** listaVenta, ST_LISTA_VENTAS ** listaRetirosPorSucursal){
    ST_LISTA_VENTAS* nodoVenta = crearNodoVentas(factura,listaVenta);
    nodoVenta->ste = *listaRetirosPorSucursal;
    *listaRetirosPorSucursal = nodoVenta;
}

void mostrar5ElementosDeCola (ST_COLA_LIBROS * colaVentas){
    ST_LISTA_VENTAS* aux = colaVentas->inicio;
    int cont = 0;
    while((cont < 5) && (aux != NULL)){
        printf("\n Venta:\n");
        printf("Factura: %i\n", aux->IDFactura);
        printf("Cant. de libros: %i\n", aux->cantLibros);
        printf("Total a pagar: %4.2f\n", aux->precioTotal);
        cont++;
        aux = aux->ste;
    }
}
void remover5ElementosDeCola (ST_COLA_LIBROS * colaVentas, FILE * ptrArchivo){
    ST_LISTA_VENTAS* auxVenta;
    ST_LISTA_LIBROS* aux;
    int cont = 0;
    while((colaVentas->inicio != NULL) && (cont < 5)){
        auxVenta = colaVentas->inicio;
        while (colaVentas->inicio->listaLibro != NULL){
            aux = colaVentas->inicio->listaLibro;
            actualizarStockReservadoPorISBN(ptrArchivo, (aux->libro).ISBN, -1);
            actualizarStockDisponiblePorISBN(ptrArchivo, (aux->libro).ISBN, -1);
            colaVentas->inicio->listaLibro = colaVentas->inicio->listaLibro->ste;
            free(aux);
        }
        colaVentas->inicio = colaVentas->inicio->ste;
        free(auxVenta);
        cont++;
    }
}

void imprimirVenta (ST_LISTA_VENTAS* ventaSeleccionada){
        printf("\n Venta:\n");
        printf("Factura: %i\n", ventaSeleccionada->IDFactura);
        printf("Cant. libros: %i\n", ventaSeleccionada->cantLibros);
        printf("Total: $%4.2f", ventaSeleccionada->precioTotal);
}

void mostrarListaVentas (ST_LISTA_VENTAS ** listaRetirosPorLocal){
    ST_LISTA_VENTAS * aux = *listaRetirosPorLocal;
    while (aux){
        imprimirVenta(aux);
        aux = aux->ste;
    }
}
ST_LISTA_VENTAS* buscarEnListaVentas (int factura, ST_LISTA_VENTAS** listaVentas){
    ST_LISTA_VENTAS* aux = *listaVentas;
    while (aux != NULL && factura != aux->IDFactura){
        aux = aux->ste;
    }
    return aux;
}


void eliminarVentaDeLista (FILE* ptrArchivo, ST_LISTA_VENTAS** listaVentas){
    int factura = 0;
    printf("\nIngrese el numero de factura correspondiente\n");
    scanf ("%i", &factura);
    ST_LISTA_VENTAS* ventaSeleccionada = buscarEnListaVentas(factura, listaVentas);
    if (ventaSeleccionada != NULL){
        system("cls");
        imprimirVenta(ventaSeleccionada);
        printf("¿Esta seguro que desea retirar esta factura? Y/N \n");
        char confirmacion = 'N';
        while (getchar() != '\n');
        scanf("%c", &confirmacion);
        if ((confirmacion == 'Y') || (confirmacion == 'y')) {
            ST_LISTA_VENTAS * aux = *listaVentas;
            while ((aux->ste != ventaSeleccionada) && (aux->ste != NULL)){
                aux = aux->ste;
            }
            aux->ste = ventaSeleccionada->ste;
            if ((aux = ventaSeleccionada)){
                *listaVentas = NULL;
            }
            while (ventaSeleccionada->listaLibro!=NULL){
                ST_LISTA_LIBROS* auxLibro = ventaSeleccionada->listaLibro;
                actualizarStockReservadoPorISBN(ptrArchivo, auxLibro->libro.ISBN, -1);
                actualizarStockDisponiblePorISBN(ptrArchivo, auxLibro->libro.ISBN, -1);
                ventaSeleccionada->listaLibro = ventaSeleccionada->listaLibro->ste;
                free(auxLibro);
            }
            free(ventaSeleccionada);
        }
    }
    else{
        printf("\n Elemento no encontrado\n");
        system("pause");
    }
}

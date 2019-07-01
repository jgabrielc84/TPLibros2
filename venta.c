#include "venta.h"
#include <time.h>

void actualizarStockReservadoLista(FILE* ptrArchivo, ST_LISTA_LIBROS** listaVentas, int cant) {
	ST_LISTA_LIBROS* aux = *listaVentas;
	while(aux) {
		actualizarStockReservadoPorISBN(ptrArchivo, aux->libro.ISBN, cant);
		aux = aux->ste;
	}
}

void actualizarStockDisponibleLista(FILE* ptrArchivo, ST_LISTA_LIBROS** listaVentas, int cant) {
	ST_LISTA_LIBROS* aux = *listaVentas;
	while(aux) {
		actualizarStockDisponiblePorISBN(ptrArchivo, aux->libro.ISBN, cant);
		aux = aux->ste;
	}
}

void elegirModoDeEntrega(FILE* ptrArchivo, int factura, ST_LISTA_LIBROS** listaVentas, ST_LISTA_VENTAS** listaRetirosPorSucursal, ST_COLA_LIBROS* colaEnviosADomicilio) {
	int opcion = -1;
	while(opcion != 1 && opcion != 2){
        system("cls");
        printf("\n[1] - Entrega a domicilio\n");
        printf("[2] - Retiro en el local\n");
        scanf("%d", &opcion);
        switch (opcion) {
        case 1:
            system("cls");
            agregarVentaACola(factura, listaVentas, colaEnviosADomicilio);
            actualizarStockReservadoLista(ptrArchivo, listaVentas, 1);
            //desreferenciamos nuestra cabecera de ventas ya que los libros ahora estan guardados en la cola.
            *listaVentas = NULL;
            break;
        case 2:
            system("cls");
            agregarVentaALista(factura, listaVentas, listaRetirosPorSucursal);
            actualizarStockReservadoLista(ptrArchivo, listaVentas, 1);
            //desreferenciamos nuestra cabecera de ventas ya que los libros ahora estan guardados en la lista.
            *listaVentas = NULL;
            break;
        }
	}
}

void imprimirFecha(int factura, FILE* ptrFactura) {
	char buffTime[lenTime];
	time_t Time;
	struct tm* timeInfo;
	time(&Time);
	timeInfo = localtime(&Time);
	strftime(buffTime, sizeof(buffTime), "%b %d %H:%M", timeInfo);
	fprintf(ptrFactura, "\n Factura %i \n Fecha: %s\n", factura, buffTime);
}

void generarNombreFactura(char* nombreFactura, int* factura) {
	char numeroFactura[lenNumeroFactura];
	strcpy(nombreFactura, "Factura");
    strcat(nombreFactura, itoa(*factura, numeroFactura, 10));
	strcat(nombreFactura, ".txt");
	FILE* ptrFactura = NULL;
	while ((ptrFactura = fopen(nombreFactura, "rb+")) != NULL) {
		(*factura)++;
		strcpy(nombreFactura, "Factura");
		strcat(nombreFactura, itoa(*factura, numeroFactura, 10));
		strcat(nombreFactura, ".txt");
		fclose(ptrFactura);
	}
}

double imprimirListaEnFactura(FILE* ptrFactura, ST_LISTA_LIBROS** listaVenta) {
	ST_LISTA_LIBROS* aux = *listaVenta;
	double totalPrecio = 0;
	while(aux){
		fprintf(ptrFactura, "\n ISBN: %s \t Titulo: %s \t Precio: %4.2f\n", aux->libro.ISBN, aux->libro.titulo, aux->libro.precio);
		totalPrecio += (aux->libro).precio;
		aux = aux->ste;
	}
	return totalPrecio;
}

int generarFactura(ST_LISTA_LIBROS** listaVenta) {
	int factura = 1;
	printf("\n Esta seguro que desea realizar la compra? Y/N\n");
	char confirmacion = 'n';
    while(getchar() != '\n');
    scanf("%c", &confirmacion);
	if((confirmacion == 'Y' || confirmacion == 'y') && *listaVenta) {
		FILE* ptrFactura = NULL;
		char nombreFactura[lenNombreFactura];
		generarNombreFactura(nombreFactura, &factura);
		if ((ptrFactura = fopen(nombreFactura, "a")) == NULL) {
			printf("La factura no pudo ser generada. Operacion cancelada.");
			return -1;
		}
		imprimirFecha(factura, ptrFactura);
		double totalPrecio = imprimirListaEnFactura(ptrFactura, listaVenta);
		fprintf(ptrFactura, "\n \t Total: \t  %4.2f \n", totalPrecio);
		fclose(ptrFactura);
	}
	else {
		factura = -1;
	}
	return factura;
}

void menuVenta(FILE* ptrArchivo, ST_LISTA_LIBROS** listaDeVenta){
    printf("\n[1] Buscar otro libro");
    printf("\n[0] Volver\n");
    int opcion = -1;
    bool buscar = false;
    while(opcion != 0 && !buscar){
        scanf("%d", &opcion);
        switch(opcion){
        case 1://buscar otro libro
            buscar = true;
            ingresarArticulosAVenta(ptrArchivo, listaDeVenta);
            break;
        }
    }
}

void ingresarArticulosAVenta(FILE* ptrArchivo, ST_LISTA_LIBROS** listaVentas){
    //buscar libro
    ST_LIBRO libro = inicializarLibro();
    int opcion = -1;
    while(opcion != 0 && strcmp(libro.ISBN, "") == 0){
        libro = inicializarLibro();
        printf("Inicio -> Ventas -> Ingresar Articulo\n");
        printf("\n[1] Buscar libro por ISBN.");
        printf("\n[2] Buscar libro por Titulo o Autor.");
        printf("\n[0] Volver\n");
        scanf("%d", &opcion);
        switch(opcion){
        case 1://buscar por isbn
            libro = buscarLibroPorISBNPorConsola(ptrArchivo);
            break;
        case 2://buscar por titulo o autor
            libro = buscarLibroPorAutorOTituloPorConsola(ptrArchivo);
            break;
        case 0:
            return;
        }
    }
    //solo ingresar libros validos
    if(strcmp(libro.ISBN, "") == 0 || libro.stockDisponible <= 0){
        printf("\nEste libro no se encuentra en stock.");
        menuVenta(ptrArchivo, listaVentas);
        return;
    }
    mostrarLibro(libro);
    printf("\nDesea ingresar este libro a la lista de venta? Y/N\n");
    char confirmacion = 'n';
    while(getchar() != '\n');
    scanf("%c", &confirmacion);
    if((confirmacion == 'Y') || (confirmacion == 'y')){
        agregarLibroALista(listaVentas, libro);
    }
    menuVenta(ptrArchivo, listaVentas);
}

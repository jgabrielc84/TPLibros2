#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED

#include "libro.h"
typedef struct listaLibros {
	ST_LIBRO libro;
	struct listaLibros* ste;
}ST_LISTA_LIBROS;

typedef struct listaVentas {
	struct listaVentas* ste;
	int IDFactura;
	int cantLibros;
	double precioTotal;
	ST_LISTA_LIBROS* listaLibro;
} ST_LISTA_VENTAS;

typedef struct {
	ST_LISTA_VENTAS* inicio;
	ST_LISTA_VENTAS* fin;
} ST_COLA_LIBROS;

void crearListaLibros(ST_LISTA_LIBROS** cabecera);
void agregarLibroALista(ST_LISTA_LIBROS** lista, ST_LIBRO libro);
ST_LIBRO extraerLibroEnPosicion(int pos, ST_LISTA_LIBROS** lista);
void printearListaLibros(ST_LISTA_LIBROS** lista);
void eliminarVentaDeLista (FILE* ptrArchivo, ST_LISTA_VENTAS** listaVentas);
void mostrarListaVentas (ST_LISTA_VENTAS ** listaRetirosPorLocal);
void mostrar5ElementosDeCola (ST_COLA_LIBROS * colaVentas);
void remover5ElementosDeCola (ST_COLA_LIBROS * colaVentas, FILE * ptrArchivo);
void agregarVentaACola (int factura, ST_LISTA_LIBROS ** listaVenta, ST_COLA_LIBROS * colaVentas);
void agregarVentaALista (int factura, ST_LISTA_LIBROS ** listaVenta, ST_LISTA_VENTAS ** listaRetirosPorSucursal);
void vaciarListaLibros(ST_LISTA_LIBROS** lista);
#endif // LISTA_H_INCLUDED

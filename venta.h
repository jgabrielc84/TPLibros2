#ifndef VENTA_H_INCLUDED
#define VENTA_H_INCLUDED
#include <stdio.h>
#include "lista.h"

#define lenTime 20
#define lenNombreFactura 20
#define lenNumeroFactura 10

void ingresarArticulosAVenta(FILE* ptrArchivo, ST_LISTA_LIBROS** listaVentas);
int generarFactura(ST_LISTA_LIBROS** listaVenta);
void actualizarStock(FILE* ptrArchivo, ST_LISTA_LIBROS** listaVentas);
void elegirModoDeEntrega(FILE* ptrArchivo, int factura, ST_LISTA_LIBROS** listaVentas, ST_LISTA_VENTAS** listaRetirosPorSucursal, ST_COLA_LIBROS* colaEnviosADomicilio);

#endif // VENTA_H_INCLUDED

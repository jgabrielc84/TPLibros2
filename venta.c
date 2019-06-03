#include "venta.h"
#include "consola.h"

void menuVenta(FILE* ptrArchivo, ST_NODO* listaDeVenta){
    printf("\n[1] Buscar otro libro");
    printf("\n[2] Volver\n");
    int n = 0;
    scanf("%d", &n);
    switch(n){
    case 1://buscar otro libro
        ingresarArticulosAVenta(ptrArchivo, listaDeVenta);
        break;
    case 2://volver
        ventaConsola(ptrArchivo, listaDeVenta);
        break;
    default:
        ventaConsola(ptrArchivo, listaDeVenta);
        break;
    }
}

void ingresarArticulosAVenta(FILE* ptrArchivo, ST_NODO* listaDeVenta){
    //buscar libro
    ST_LIBRO libro = buscarLibroIesimo(buscarLibroPorISBNPorConsola(ptrArchivo), ptrArchivo);
    if(libro.stockDisponible <= 0){
        printf("\nEste libro no se encuentra en stock.");
        menuVenta(ptrArchivo, listaDeVenta);
        return;
    }
    mostrarLibro(libro);
    printf("\nDesea ingresar este libro a la lista de venta? Y/N\n");
    char confirmacion = 'n';
    while(getchar() != '\n');
    scanf("%c", &confirmacion);
    if((confirmacion == 'Y') || (confirmacion == 'y')){
        insertarNodo(&listaDeVenta, libro);
    }
    menuVenta(ptrArchivo, listaDeVenta);

}

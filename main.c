#include <stdio.h>
#include <stdlib.h>
#include "cadena.h"
#include "libro.h"
#include "consola.h"



int main()
{
    ST_LIBRO libros [cant_lib];
    inicializarLibros(libros, cant_lib);
    crearLibro("La vida de Paula", crearAutor("Paula", "Monti"), 20.0, "1", 5000, 1, libros);
    crearLibro("La vida de Gabriel", crearAutor("Gabriel Juan", "Chavez"), 10.0, "987256202", 5, 0, libros);
    crearLibro("Mi maravillosa vida", crearAutor("Ignacio Julian", "Venezia"), 50000.0, "987256202", 0, 5000, libros);
    iniciarConsola(libros);
    return 0;
}

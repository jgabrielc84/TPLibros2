#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include "libro.h"

typedef struct nodo{
    ST_LIBRO libro;
    int pos;
    struct ST_NODO* siguiente;
}ST_NODO;

void insertarNodo(ST_NODO** lista, ST_LIBRO libro);
ST_LIBRO extraerNodo(ST_NODO** lista);
ST_LIBRO extraerIesimoNodo(ST_NODO**, int iesimo);
bool hasNext(ST_NODO* nodo);

#endif // LISTA_H_INCLUDED

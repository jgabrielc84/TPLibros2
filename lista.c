#include "lista.h"

/*void crearNodo(ST_NODO** nodo){
    *nodo = (ST_NODO*)malloc(sizeof(ST_NODO));
    (*nodo)->libro = NULL;
    (*nodo)->siguiente = NULL;
    (*nodo)->pos = 0;
}
*/
ST_NODO* crearNodo(){
    ST_LIBRO libro;
    ST_NODO* nodo = (ST_NODO*)malloc(sizeof(ST_NODO));
    nodo->libro = libro;
    nodo->siguiente = NULL;
    nodo->pos = 0;
    return nodo;
}

void insertarNodo(ST_NODO** lista, ST_LIBRO libro){
    ST_NODO* nodo = crearNodo();
    nodo->siguiente = *lista;
    nodo->libro = libro;
    if(*lista)
        nodo->pos = (*lista)->pos + 1;
    *lista = nodo;
}

ST_LIBRO extraerNodo(ST_NODO** lista){
    ST_LIBRO libro = (*lista)->libro;
    ST_NODO* aux = *lista;
    *lista = (*lista)->siguiente;
    free(aux);
    return libro;
}

ST_LIBRO extraerIesimoNodo(ST_NODO** lista, int iesimo){
    ST_NODO* aux = *lista;
    for(int i = 0; i < iesimo; i++){
        aux = aux->siguiente;
    }
    ST_LIBRO libro = (*aux).libro;
    return libro;
}

bool hasNext(ST_NODO* nodo){
    return nodo->siguiente != NULL;
}

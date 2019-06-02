#include "cadena.h"

int contarCadena(const char* cadena){
        int cont = 0;
        while (*cadena != '\0'){
            cadena++;
            cont++;
        }
    return cont;
}

bool buscarCoincidencia(const char* cadenaIngresada, const char* cadenaExistente){
    bool coincidencia = 0;
    int cont = 0;
    int tamanioCadenaIngresada = contarCadena(cadenaIngresada);
    const char *posicionInicial = cadenaIngresada;
    while((*cadenaExistente != '\0') && (*cadenaIngresada != '\0')){
            //simplificar este if por dios!
        if((*cadenaIngresada == *cadenaExistente) || ((*cadenaIngresada <= 90) && (*cadenaIngresada >= 65) && (*cadenaIngresada == *cadenaExistente - 32)) || ((*cadenaIngresada <= 122) && (*cadenaIngresada >= 97) && (*cadenaIngresada == *cadenaExistente + 32))){
            cadenaExistente++;
            cadenaIngresada++;
            cont ++;
        }
        else {
            cadenaExistente++;
            cadenaIngresada = posicionInicial;
            cont = 0;
        }
    }
    if(cont == tamanioCadenaIngresada){
        coincidencia = 1;
    }
    return coincidencia;
}

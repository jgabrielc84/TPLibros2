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

bool contieneSubCadena(const char* cadenaIngresada, const char* cadenaExistente){
    if(!cadenaIngresada || !cadenaExistente || contarCadena(cadenaIngresada) > contarCadena(cadenaExistente)){
        return false;
    }
    const char* auxSrc = cadenaIngresada;
    const char* auxDest = cadenaExistente;
    bool foundSub = false;
    while(*auxSrc && *auxDest){
        if(foundSub){
            //if(*auxSrc == *auxDest){
            if((*auxSrc == *auxDest) || ((*auxSrc <= 90) && (*auxSrc >= 65) && (*auxSrc == *auxDest - 32)) || ((*auxSrc <= 122) && (*auxSrc >= 97) && (*auxSrc == *auxDest + 32))){
                auxSrc++;
                auxDest++;
            }else{
                foundSub = false;
                auxSrc = cadenaIngresada;
            }
        }else{
            if((*auxSrc == *auxDest) || ((*auxSrc <= 90) && (*auxSrc >= 65) && (*auxSrc == *auxDest - 32)) || ((*auxSrc <= 122) && (*auxSrc >= 97) && (*auxSrc == *auxDest + 32))){
                foundSub = true;
            }else{
                auxDest++;
            }
        }
    }
    if(*auxSrc){
        return false;
    }
    return foundSub;
}

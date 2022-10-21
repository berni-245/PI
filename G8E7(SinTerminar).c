#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILS 6
#define COLUM 7
#define BLOQUE 10

typedef enum {DER=0, IZQ, ABA, ARR, I_AR, I_AB, D_AR, D_AB} Tdireccion;

typedef struct{
    char * palabra;
    size_t fila;
    size_t columna;
    Tdireccion direccion;
}posicion;

int
main(){
    char sopa[FILS][COLUM] = {{'a','a'},
                              {'a','a'}};

    char * palabras[] = {""};

    posicion * encontrado;

    encontrado = resolverSopa(sopa, palabras);
}




posicion * 
resolverSopa(char sopa[FILS][COLUM], char * diccionario[]){
    int i, dimResp = 0;
    posicion * resp;

    resp = NULL;

    for(i=0; diccionario[i][0] != '\0'; i++){
        resp = buscarPalabra(sopa, diccionario[i], &dimResp);
    }

    resp = realloc(resp, (dimResp+1)*sizeof(posicion));
    resp[dimResp].palabra = NULL;

    return resp;
}

posicion *
buscarPalabra(char sopa[FILS][COLUM], char palabra[], int * dimResp){
    int i, j;
    posicion * resp;

    for(i=0; i<FILS; i++){
        for(j=0; j<COLUM; j++){
            if(sopa[i][j] == palabra[0]){
                resp = recorrerDirecciones(sopa, palabra, dimResp, i, j);
            }
        }
    }
    
    return resp;

}


posicion *
recorrerDirecciones(char sopa[FILS][COLUM], char palabra[], int * dimResp, int x0, int y0){
    Tdireccion direcciones;
    posicion * resp;

    for(direcciones = DER; direcciones <= D_AB; direcciones++){
        resp = camino(sopa, palabra, dimResp, direcciones, x0, y0);
    }

}

posicion *
camino(char sopa[FILS][COLUM], char palabra[], int * dimResp, Tdireccion direActual, int x0, int y0){
    int i, j;
    int dirx, diry;
    transformarXY(direActual, &dirx, &diry);
    i = x0 + dirx;
    j = y0 + diry;
    //incompleto
}


void
transformarXY(Tdireccion direActual, int * dirx, int * diry){
    int direcciones[8][2] = {{1,0}, {-1,0}, {0,-1}, {0,1}, {-1,1}, {-1,-1}, {1,1}, {1,-1}};
    *dirx = direcciones[direActual][0];
    *diry = direcciones[direActual][1];
}

//cómo estoy repetiendo muchos parámetros en las funciones, tal vez conviene agruparlos en un struct
//CREO que no podemos retornar la resp cómo posicion *, porque si llego a no tener que cambiar nada, no puedo no retornar algo
//hay que pasar resp cómo parámetros

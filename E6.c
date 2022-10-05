#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "../getnum.h"
#include "../random.h"
#define NUM_CANT 3
#define DIM_CANDIDATOS 10

void generaAleatorio(int num[]); 
int elegirNivel(); //front
void leerNumero(int num[]); //front
bool coincideNumero(const int resp[],const int respUser[]); //back y front
int cantidadBien(const int resp[], const int respUser[]);
int cantidadRegular(const int resp[],const int respUser[]);
 
int main(){
    int resp[NUM_CANT], respUser[NUM_CANT];
    int i, intentos, coincide = false;

    generaAleatorio(resp);
    intentos = elegirNivel();

    while(intentos != 0 && coincide == false){
        leerNumero(respUser);
        coincide = coincideNumero(resp, respUser);
        --intentos;
    }

    if(coincide == false){
        printf("Lo siento, el numero es ");
        for(i=0; i<NUM_CANT; i++){
            printf("%d",resp[i]);
        }
        putchar('\n');
    }
    else{
        printf("Acertaste! El numero era ");
        for(i=0; i<NUM_CANT; i++){
            printf("%d",resp[i]);
        }
        putchar('\n');
    }

    return  0;
}

void
generaAleatorio(int num[]){
    int i,j, aux;
    int candidatos[] = {0,1,2,3,4,5,6,7,8,9};
    randomize();

    for(i=0;i<DIM_CANDIDATOS;i++){
        j = randInt(0,DIM_CANDIDATOS-1);
        aux = candidatos[i];
        candidatos[i] = candidatos[j];
        candidatos[j] = aux;
    }

    for(i=0; i<NUM_CANT; i++){
        num[i] = candidatos[i];
    }
}

int
elegirNivel(){
    size_t dificultad;
    do{
        dificultad = getint("Ingrese la cantidad de intentos que desea tener: ");
        putchar('\n');
    }while(dificultad <= 0);
    return dificultad;
}

void
leerNumero(int numeroFinal[]){
    int i, resp, flag = false, max = pow(10, NUM_CANT);
    int divisor = max/10;

    do{
        resp = getint("Ingrese un numero de %d cifras (menos cifras = rellena con 0): ",NUM_CANT);
        if(resp >= 0 && resp < max)
            flag = true;
    }while(flag == false);

    for(i=0; i<NUM_CANT;i++){
        numeroFinal[i] = resp/divisor;
        resp %= divisor;
        divisor /= 10;
    }
    
}

bool
coincideNumero(const int resp[],const int respUser[]){
    int i=0, coincide= true;
    int cantBien, cantReg;

    while(i < NUM_CANT && coincide == true){
        if(resp[i] != respUser[i])
            coincide = false;
        i++;
    }

    if(coincide == false){
        cantBien = cantidadBien(resp,respUser);
        cantReg = cantidadRegular(resp,respUser);

        printf("%d bien, %d regular\n", cantBien, cantReg);
    }

    return coincide;
}

int
cantidadBien(const int resp[], const int respUser[]){
    int i, count=0;
    for(i=0; i<NUM_CANT;i++){
        if(resp[i] == respUser[i])
            count++;
    }
    return count;
}
 
int
cantidadRegular(const int resp[], const int respUser[]){
    int i, j, found, count=0;

    for(i=0; i<NUM_CANT; i++){
        found = true;
        for(j=0;j<NUM_CANT && found==true; j++){
            if(j==i)
                j++;
            if(j < NUM_CANT && resp[j] == respUser[i]){
                count++;
                found=false;
            }
        }
    }

    return count;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../random.h"

#define CANT_FIGURAS 13
#define CANT_PALOS 4
#define CARTAS_MAZO CANT_FIGURAS*CANT_PALOS
#define CARTAS_JUGADOR 5

typedef struct{
    short numero, palo;  // numero de 0 a 12, palo de 0 a 3
}carta;

//cartas es un vector de varios struct carta
typedef carta cartas[CARTAS_MAZO];

//Cantidad de cartas para cada jugador en cada mano
typedef carta jugador[CARTAS_JUGADOR]; 

//genera y mezcla el mazo
void prepararMazo(cartas mazo);

//toma el mazo actual y devuelve un vector de 5 cartas por jugador, y la nueva dimensión del mazo
void repartirCartas(cartas mazo, int * dim, jugador jugadorX);

//imprime la mano actual de un jugador
void imprimirMano(jugador jugadorX);

//checkea si la mano actual de un jugador tiene algún PAR/PIERNA/POKER 
void checkearMano(jugador jugadorX);

int
main(){
    cartas mazo;
    jugador jugador1;
    int dim = CARTAS_MAZO;

    randomize();
    prepararMazo(mazo);
    

    do{
        repartirCartas(mazo, &dim, jugador1);

        imprimirMano(jugador1);
        checkearMano(jugador1);
        sleep(2); //Para darle un mejor ritmo al juego

    }while(dim >= CARTAS_JUGADOR);
    
    
    printf("FIN.\n");


    return 0;
}

void
prepararMazo(cartas mazo){
    int i, j, aux1, aux2;
    
    //algoritmo válido solamente si CANT_FIGURAS Y CANT_PALOS son coprimos (al menos eso parece por testeos)
    for(i=0; i<CARTAS_MAZO; i++){
        mazo[i].numero = i%CANT_FIGURAS;
        mazo[i].palo = i%CANT_PALOS;                
    }  


    for(i=0; i<CARTAS_MAZO; i++){
        j = randInt(0, CARTAS_MAZO-1);
        aux1 = mazo[i].numero;
        aux2 = mazo[i].palo;
        mazo[i].numero = mazo[j].numero;
        mazo[i].palo = mazo[j].palo;
        mazo[j].numero = aux1;
        mazo[j].palo = aux2;
    }   
}

void
repartirCartas(cartas mazo, int * dim, jugador jugadorX){
    int i, j, newDim = *dim;

    for(i=0; i<CARTAS_JUGADOR; i++){
        j = randInt(0, newDim-1);

        jugadorX[i].numero = mazo[j].numero;
        jugadorX[i].palo = mazo[j].palo;

        mazo[j].numero = mazo[newDim-1].numero;
        mazo[j].palo = mazo[newDim-1].palo;

        newDim--;
    }

    *dim = newDim;
}

void
imprimirMano(jugador jugadorX){
    char * numeros[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","As"};
    char * palos[] = {"Corazon","Trebor","Pica","Diamante"};

    int i;
    for(i=0; i<CARTAS_JUGADOR; i++){
        printf("Numero:%s\t Palo:%s\n", numeros[jugadorX[i].numero], palos[jugadorX[i].palo]);
    }
    putchar('\n');
}

void
checkearMano(jugador jugadorX){
    int i, j, cantPar = 0, cantPierna = 0, cantPoker = 0;
    short marcas[CARTAS_JUGADOR] = {1,1,1,1,1};//todos aparecen al menos una vez

    for(i=0; i<CARTAS_JUGADOR; i++){
        for(j=i+1; j<CARTAS_JUGADOR; j++){
            if(jugadorX[j].numero != -1 && (jugadorX[i].numero == jugadorX[j].numero)){
                marcas[i]++;
                jugadorX[j].numero = -1; //para evitar marcar dos veces el mismo número
                }
        }
        
    }

    /*
    para testear

    //marcas[0] = 4;

    for(i=0; i<CARTAS_JUGADOR; i++){
        printf("%d ", marcas[i]);
    }
    putchar('\n');
    putchar('\n');
    */


    for(i = 0; i<CARTAS_JUGADOR; i++){
        if(marcas[i] == 2)
            cantPar++;
        if(marcas[i] == 3)
            cantPierna++;
        if(marcas[i] == 4)
            cantPoker++;
    }

    printf("El jugador hizo %d par, %d pierna, %d poker\n", cantPar, cantPierna, cantPoker);
    putchar('\n');

}

/*
Dudas:
1) Está bien el algoritmo para generar el mazo? O debería contemplar que CANT_PALOS y CANT_FIGURAS no sean los típicos del mazo francés? (4 palos y 13 figuras)
2) Está bien la estructura general del programa? Me inquieta un poco que todas las funciones me retornaran void jaja
3) La última función quedó medio "rara", hay alguna forma más eficiente de plantearla?
PD: Puede correr el programa en mi compu si hace falta checkear algún caso
*/

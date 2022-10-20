#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../random.h"

#define CANT_FIGURAS 13
#define CANT_PALOS 4
#define CARTAS_MAZO (CANT_FIGURAS*CANT_PALOS)
#define CARTAS_JUGADOR 5
#define CONFIG_ESPECIALES 3
#define JUGADORES 2 //no se puede modificar esta variable

typedef struct{
    short numero, palo;  // numero de 0 a 12, palo de 0 a 3
}carta;

//cartas es un vector de varios struct carta
typedef carta cartas[CARTAS_MAZO];

//Cantidad de cartas para cada jugador en cada mano
typedef carta jugador[CARTAS_JUGADOR]; 

//genera el mazo
void prepararMazo(cartas mazo);

//toma el mazo actual y devuelve un vector de 5 cartas aleatorias por jugador, y la nueva dimensión del mazo
void repartirCartas(cartas mazo, int * dim, jugador jugadorX);

//imprime la mano actual de un jugador
void imprimirMano(jugador jugadorX);

//checkea quien es el ganador de la mano actual
int checkearMano(jugador jugadorX, jugador jugadorY);

//imprime y retorna las configuraciones 
void imprimirConfiguracion(short marcas[], short config[]);

//revisa si tienen la misma configuracion
bool checkEquivalencia(short configX[], short configY[]);

//calcula el paso total de la mano de un jugador (CASO: ambos jugadores tienen las mismas configuraciones)
int calcPeso(jugador jugadorX, short marcas[]);

int
main(){
    cartas mazo;
    jugador jugador1, jugador2;
    int ganador, dim = CARTAS_MAZO;
    int countJug1 = 0, countJug2 = 0;
    bool continuar = true;
    char input;

    randomize();
    prepararMazo(mazo);
    

    do{
        repartirCartas(mazo, &dim, jugador1);
        repartirCartas(mazo, &dim, jugador2);

        printf("Jugador 1:\n");
        imprimirMano(jugador1);
        printf("Jugador 2:\n");
        imprimirMano(jugador2);

        ganador = checkearMano(jugador1, jugador2);

        if(ganador == 1)
            countJug1++;
        else if(ganador == 2)
            countJug2++;
        else{
            countJug1++;
            countJug2++;
        }

        if(dim >= CARTAS_JUGADOR*JUGADORES){
        printf("Presione ENTER para continuar, presione cualquier otra cosa para parar de jugar: ");
        input = getchar();
        if(input != '\n')
            continuar = false;
        }

    }while(continuar == true && dim >= CARTAS_JUGADOR*JUGADORES); //si no puedo repartir una mano completa a cadajugador -> fin

    if(countJug1 >= countJug2)
        printf("El ganador es el jugador 1!\n");

    if(countJug2 >= countJug1)
        printf("El ganador es el jugador 2!\n");
        
    
    
    printf("FIN.\n");


    return 0;
}

void
prepararMazo(cartas mazo){
    int i;
    
    for( i = 0; i < CARTAS_MAZO; i++){
        mazo[i].numero = i%CANT_FIGURAS;
        mazo[i].palo = i/CANT_FIGURAS;    
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
    static char * numeros[] = {"2","3","4","5","6","7","8","9","10","J","Q","K","As"};
    static char * palos[] = {"Corazon","Trebor","Pica","Diamante"};

    int i;
    for(i=0; i<CARTAS_JUGADOR; i++){
        printf("Numero:%s\t Palo:%s\n", numeros[jugadorX[i].numero], palos[jugadorX[i].palo]);
    }
    putchar('\n');
}

int
checkearMano(jugador jugadorX, jugador jugadorY){
    int i, j, ganador, totalX=0, totalY=0;
    short marcasX[CARTAS_JUGADOR] = {1,1,1,1,1};//todos aparecen al menos una vez
    short marcasY[CARTAS_JUGADOR] = {1,1,1,1,1};
    short configX[] = {0,0,0}; //Para Imprimir la cantidad de par/pierna/poker
    short configY[] = {0,0,0};

    for(i=0; i<CARTAS_JUGADOR; i++){
        for(j=i+1; j<CARTAS_JUGADOR; j++){
            if(jugadorX[j].numero != -1 && (jugadorX[i].numero == jugadorX[j].numero)){
                marcasX[i]++;
                jugadorX[j].numero = -1; //para evitar marcar dos veces el mismo número
                }

            if(jugadorY[j].numero != -1 && (jugadorY[i].numero == jugadorY[j].numero)){
                marcasY[i]++;
                jugadorY[j].numero = -1; 
                }            
        }
    }

    imprimirConfiguracion(marcasX, configX);
    imprimirConfiguracion(marcasY, configY);

    if(checkEquivalencia(configX, configY) == true){ //Si tiene la misma config, veo cuál tiene más peso
        totalX = calcPeso(jugadorX, marcasX);
        totalY = calcPeso(jugadorY, marcasY);
    }
    else{
        totalX = (configY[0] & 1) + (configX[0] & 2)*2 + configX[1]*3 + configX[2]*5; //creo un peso para que poker > pierna+par > pierna > 2par > par
        totalY = (configY[0] & 1) + (configY[0] & 2)*2 + configY[1]*3 + configY[2]*5; 
    }
    
    ganador = (totalX >= totalY) + 2 * (totalY >= totalX); //1 bit= gana jug1, 2 bit= gana jug2, 3 bit= ganan ambos
    return ganador;

}

void
imprimirConfiguracion(short marcas[], short config[]){
    int i;

    for(i = 0; i<CARTAS_JUGADOR; i++){
        if(marcas[i] == 2)
            config[0]++;
        else if(marcas[i] == 3)
            config[1]++;
        else if(marcas[i] == 4)
            config[2]++;
    }

    printf("El jugador hizo %d par, %d pierna, %d poker\n", config[0], config[1], config[2]);
    putchar('\n');

}

bool
checkEquivalencia(short configX[], short configY[]){
    bool equivalencia = true;
    int i;
    
    for(i=0; i<CONFIG_ESPECIALES && equivalencia==true; i++){
        if(configX[i] != configY[i])
            equivalencia = false;
    }

    return equivalencia;
}

int
calcPeso(jugador jugadorX, short marcas[]){
    int i, total=0;
    for(i=0; i<CARTAS_JUGADOR; i++){
        if(jugadorX[i].numero != -1) //si no está marcado cómo repetido
            total += marcas[i]*(jugadorX[i].numero + 2); 
    }
    return total;
}

//evitar el uso de magic numbers, usar más define/enum de ser necesario
//se podría usar un struct para la mano del jugador, sus marcas y configuraciones en lugar de hacerlo en varias variables

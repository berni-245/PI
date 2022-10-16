#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../random.h"

#define CARTAS_MAZO 52
#define CANT_FIGURAS 13
#define CANT_PALOS 4
#define CARTAS_JUGADOR 5
#define LETRAS_PALO 8

//Acá declaré el enum por si le encontraba uso más adelante
typedef enum posNumeros{AZ=1,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE,DIEZ,J,Q,K} numeros;

typedef struct{
    int numero;
    char palo[LETRAS_PALO+1];  
}carta;

//cartas es un vector de varios struct carta
typedef carta cartas[CARTAS_MAZO];

//Acá utilicé un puntero porque no sé si debería contemplar los casos cuando reparto algo menor a 5 cartas
typedef carta * jugador; 

//genera y mezcla el mazo
void prepararMazo(cartas mazo);

//toma el mazo actual y devuelve un vector de 5 cartas por jugador, y la nueva dimensión del mazo
jugador * repartirCartas(cartas mazo, int * dim);

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
    
    int i;
    for(i=0; i<CARTAS_MAZO; i++){
        printf("%d %s\n",mazo[i].numero,mazo[i].palo);
    }
    
    do{
        jugador1 = repartirCartas(mazo, &dim);

        imprimirMano(jugador1);
        checkearMano(jugador1);

    }while(dim > 0); //o "dim >= CARTAS_JUGADOR" si sólo quisiera repartir de a 5
    
    printf("FIN.\n");


    return 0;
}

void
prepararMazo(cartas mazo){
    int i, j, aux;
    short index[CARTAS_MAZO];
    char * palos[] = {"corazon","trebol","pica","diamante"};
    numeros numeroActual = AZ-1;

    for(i=0; i<CARTAS_MAZO; i++){
        index[i] = i;   //índices de 0 a 51
    }

    for(i=0; i<CARTAS_MAZO; i++){ //desordeno los índices
        j = randInt(0,CARTAS_MAZO-1);
        aux = index[i];
        index[i] = index[j];
        index[j] = aux;
    }
    
    for(i=0; i<CARTAS_MAZO; i++,j++){
        if(!(i%CANT_PALOS)){
            numeroActual++;
            j=0;
        }
        
        //En lugar de asignarlos en orden ascendente, los asigno en el orden aleatorio de los índices que quedaron antes

        mazo[index[i]].numero = numeroActual; 
        strcpy(mazo[index[i]].palo, palos[j]);
                
    }       
}


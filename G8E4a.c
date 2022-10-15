#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define CARTAS_MAZO 52
#define CANT_FIGURAS 13
#define CANT_PALOS 4
#define CARTAS_JUEGO 5
#define LETRAS_PALO 8
enum posNumeros{AZ=1,DOS,TRES,CUATRO,CINCO,SEIS,SIETE,OCHO,NUEVE,DIEZ,J,Q,K};

typedef struct{
    int numero;
    char palo[LETRAS_PALO+1];  
}carta;

typedef carta cartas[CARTAS_MAZO];
typedef carta * jugador; 

void generarMazo(cartas mazo);
void mezclarMazo(cartas mazo);
jugador * repartirCartas(cartas mazo, int * dim);
void checkearMano(jugador jugadorX);
void imprimirMano(jugador jugadorX);

int
main(){
    cartas mazo;
    jugador jugador1;
    int dim = CARTAS_MAZO;

    generarMazo(mazo);

    do{
        jugador1 = repartirCartas(mazo, &dim);
        checkearMano(jugador1);
        imprimirMano(jugador1);

    }while(dim > 0);
    printf("FIN.\n");


    return 0;
}

void
generarMazo(cartas mazo){
    int i, j;
    char * palos[] = {"corazon","trebol","pica","diamante"};
    enum posNumeros numeroActual;
    numeroActual = AZ-1;
    
    for(i=0, j=0; i<CARTAS_MAZO; i++,j++){
        if(i%CANT_PALOS){
            numeroActual++;
            j=0;
        }

        mazo[i].numero = numeroActual;
        strcpy(mazo[i].palo, palos[j]);
                
    }
    //4 cartas del número 1 pero distinto palo
    //las siguietes 4 sean del numero 2 pero de distinto palo
}

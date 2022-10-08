#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../random.h"
#define CANT_BOLILLAS_INI 90
#define PLAYERS 2
#define LINEAS 3
#define COLUM 5
typedef int TipoLinea[COLUM];
typedef TipoLinea TipoCarton[LINEAS]; //carta[3][5]

void generarCarton(TipoCarton carton);
int jugar(int bolillero[], TipoCarton jugador1, TipoCarton jugador2);
int sacarBolilla(int bolillero[], int * cantBolillas);
int controlarCarton(TipoCarton carton, int bolilla);
void imprimirCarton(TipoCarton carton);
int buscarBolilla(TipoCarton carton, int bolilla);
int controlarLineas(TipoLinea linea);

int
main(){
    TipoCarton jugador1, jugador2;
    int bolillero[CANT_BOLILLAS_INI];
    int check, i;

    for(i=0; i<CANT_BOLILLAS_INI;i++){
        bolillero[i] = i + 1; //llenamos el bolillero
    }

    randomize();

    generarCarton(jugador1);
    generarCarton(jugador2);

    check = jugar(bolillero, jugador1, jugador2);

    for(i = 1; i <= PLAYERS; i++){
        if(check & i)
            printf("El jugador %d hizo bingo\n", i);
    }

    return 0;    
}

void
generarCarton(TipoCarton carton){
    int i, j, k;
    int candidatos[CANT_BOLILLAS_INI];
    int indiceMax = CANT_BOLILLAS_INI - 1;

    for(i = 0; i<CANT_BOLILLAS_INI; i++){
        candidatos[i] = i + 1;//0 puede usarse de flag de marcado en los cartones
    }

    for(i=0;i<LINEAS; i++){
        for(j=0; j<COLUM; j++){
            k = randInt(0, indiceMax);
            carton[i][j] = candidatos[k];
            candidatos[k] = candidatos[indiceMax--];
        }
    }
}

int
jugar(int bolillero[], TipoCarton jugador1, TipoCarton jugador2){
    /*
    Para variable ganador:
    0 -> 0bit -> no winners yet, seguir loopeando
    1 -> 1bit -> gana jugador 1
    2 -> 1bitEnOtroLado -> gana jugador 2
    3 -> 1bitEnAmbosLados -> gana jugador 1 y 2
    */
    int i, bolilla, ganador = 0; 
    int restantes = CANT_BOLILLAS_INI;
    int lineasJug1 = 0, lineasJug2 = 0, firstLine = 0;


    do{
        printf("Jugador 1:\n");
        imprimirCarton(jugador1);
        printf("Jugador 2:\n");
        imprimirCarton(jugador2);

        bolilla = sacarBolilla(bolillero, &restantes);
        printf("Bolilla actual: %d\n",bolilla);

        lineasJug1 = controlarCarton(jugador1, bolilla);
        lineasJug2 = controlarCarton(jugador2, bolilla);

        if(!firstLine && (lineasJug1 > 0 || lineasJug2 > 0)){
            printf("%s",(lineasJug1>0?"El jugador 1 hizo linea!\n":""));
            printf("%s",(lineasJug2>0?"El jugador 2 hizo linea!\n":""));

            firstLine = 1;
        }


        if(lineasJug1 == 3 && lineasJug2 == 3) //si ganan los dos en esta ronda
            ganador = 3;
        else if(lineasJug1 == 3 || lineasJug2 == 3) //si gana sólo uno
            ganador = lineasJug1>lineasJug2? 1:2;  



    }while(ganador == 0);
    
    return ganador;
}

int
sacarBolilla(int bolillero[], int * cantBolillas){
    int i, bolilla;

    /*
    - reduzco la dimensión actual
    - tomo índice entre 0 y cantidad actual menos 1 (ya la decremente en el paso anterior) 
    - tomo la bolilla aleatoria
    - intercambio la bolilla aleatoria con la última para no perder candidatos total no voy a acceder a la última pues reduje la dimensión
    */

    (*cantBolillas)--; 
    i = randint(0, *cantBolillas); 

    bolilla = bolillero[i]; 
    bolillero[i] = bolillero[*cantBolillas]; 

    return bolilla; 

}

void
imprimirCarton(TipoCarton carton){
    int i, j;

    for(i=0; i<LINEAS; i++){
        for(j=0; j<COLUM; j++){
            if(carton[i][j] != 0)
                printf("%2d ", carton[i][j]);
            else
                printf("%2c ", 'X');
        }
        putchar('\n');
    }
    putchar('\n');
}

int
controlarCarton(TipoCarton carton, int bolilla){
    int i, found, checkLineas = 0;

    found = buscarBolilla(carton, bolilla);
    if(found){
        for(i=0; i<LINEAS; i++){
            checkLineas += controlarLineas(carton[i]);
        }
    }

    return checkLineas;
}

int
buscarBolilla(TipoCarton carton, int bolilla){
    int i, j;

    for(i=0; i<LINEAS; i++){
        for(j=0; j<COLUM; j++){
            if(carton[i][j] == bolilla){
                carton[i][j] = 0;
                return 1;
            }
        }
    }

    return 0;
}

int
controlarLineas(TipoLinea linea){
    
}

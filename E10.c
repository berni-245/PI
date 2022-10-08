#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../random.h"
#define LONG_LETRAS 10
#define INTENTOS_INI 6

void selecPalabra(char candidatos[][LONG_LETRAS+1], char palabra[]);
char ingresarLetra();
int controlarLetra(char palabra[], char letra, short marcas[]);
void imprimirPalabra(char palabra[], short marcas[]);
int palabraCompleta(char palabra[], short marcas[]);

int
main(){
    char candidatos[][LONG_LETRAS+1] = {"test","despreciar","explotador","futbolista","interrogar","justiciero","relevancia","septiembre","voluntario"};
    char palabra[LONG_LETRAS+1];
    short marcas[LONG_LETRAS] = {0};
    int i, gano, intentos = INTENTOS_INI;
    char letra;

    randomize();
    selecPalabra(candidatos, palabra);

    do{
        imprimirPalabra(palabra, marcas);

        printf("Le quedan %d intentos restantes\n",intentos);
        letra = ingresarLetra();
        intentos -= (controlarLetra(palabra, letra, marcas) != 1);

        gano = palabraCompleta(palabra, marcas);
    
    }while(intentos != 0 && !gano);

    if(gano){
            printf("Felicidades, acertaste! La palabra era:\n");
            imprimirPalabra(palabra, marcas);
    }
    else{
        for(i=0; palabra[i] != '\0'; i++){
            marcas[i] = 1;
        }

        printf("Lo siento! La palabra era:\n");
        imprimirPalabra(palabra, marcas);
    }
        

    return 0;
}

void
selecPalabra(char candidatos[][LONG_LETRAS+1], char palabra[]){
    int i = randInt(0, LONG_LETRAS-1);
    int j;

    for(j=0; j<=LONG_LETRAS; j++){
        palabra[j] = candidatos[i][j];
    }

}

char
ingresarLetra(){
    char letra;

    printf("Ingrese una letra: ");
    while(!isalpha(letra = getchar()));

    return tolower(letra);
}

int 
controlarLetra(char palabra[], char letra, short marcas[]){
    int i, found=0;

    for(i=0; palabra[i] != '\0'; i++){
        if(palabra[i] == letra){
            marcas[i] = 1;
            found = 1;
        }
    }

    return found;
}
void 
imprimirPalabra(char palabra[], short marcas[]){
    int i;

    for(i=0; palabra[i]; i++){
        if(marcas[i])
            putchar(palabra[i]);
        else
            putchar('_');
        putchar(' ');
    }
    putchar('\n');
    putchar('\n');
}

int 
palabraCompleta(char palabra[], short marcas[]){
    int i, gano = 1;

    for(i=0; palabra[i] && gano; i++){
        if(marcas[i] != 1){
            gano = 0;
        }
    }

    return gano;
    
}

#include <stdbool.h>
#define BORRA_BUFFER while (getchar() != '\n')
#define NUM_CANT 3

void
leerNumero(int numFinal[]){
    char numero[NUM_CANT+1];
    char cond[6];
    int i, coherencia, cant, digito;

    sprintf(cond,"%%%ds", NUM_CANT); // NUM_CANT = 5 -> %5s

    printf("Ingrese su respuesta (cantidad de digitos= %d): ",NUM_CANT);
    do{
        coherencia = true;
        cant = scanf(cond, numero);
        BORRA_BUFFER;

        if(strlen(numero) != NUM_CANT)
            coherencia = false;

        for(i=0;isdigit(numero[i]) && numero[i]!='\0';i++){
            numFinal[i] = numero[i]-'0';
        }
        if(i == NUM_CANT)
            coherencia = true;

    }while(coherencia == false && cant != 1);
}

//conclusión: los scand son raros

#include <stdlib.h>
#include <stdio.h>
#include "E5.h"

typedef struct complexCDT{
    double real;
    double imag;
} complexCDT;

double
real(complexADT numero){
    return numero->real;
}

double
imag(complexADT numero){
    return numero->imag;
}

complexADT
sumaComplex(complexADT numero1, complexADT numero2){
    complexADT aux = malloc(sizeof(complexCDT)); //*aux
    aux->real = numero1->real + numero2->real;
    aux->imag = numero1->imag + numero2->imag;
    
    return aux;
}

complexADT
newComplex(double real, double imag){
    complexADT aux = malloc(sizeof(*aux));//complexCDT
    aux->real = real;
    aux->imag = imag;

    return aux;
}

void
freeComplex(complexADT numero){
    free(numero);
}

complexADT
restaComplex(complexADT numero1, complexADT numero2){
    complexADT aux = malloc(sizeof(*aux));
    aux->real = numero1->real - numero2->real;
    aux->imag = numero1->imag - numero2->imag;

    return aux;
}

complexADT
multComplex(complexADT numero1, complexADT numero2){
    complexADT aux = malloc(sizeof(*aux));
    aux->real = numero1->real * numero2->real - numero1->imag * numero2->imag;
    aux->imag = numero1->real * numero2->imag + numero1->imag * numero2->real;

    return aux;
}

complexADT
conjuComplex(complexADT numero){
    complexADT aux = malloc(sizeof(*aux));
    aux->real = numero->real;
    aux->imag = numero->imag * -1;

    return aux;
}

complexADT
divComplex(complexADT numero1, complexADT numero2){
    complexADT conjugadoNum2 = conjuComplex(numero2);
    complexADT respuesta = multComplex(numero1, conjugadoNum2);

    double denominador = numero2->real * conjugadoNum2->real + numero2->imag * conjugadoNum2->imag;
    respuesta->real /= denominador;
    respuesta->imag /= denominador;

    freeComplex(conjugadoNum2);

    return respuesta;
}

#ifndef E5_H
#define E5_H

typedef struct complexCDT * complexADT; //el tipo que manejará el usuario

//genero el complejo en el heap
complexADT newComplex(double real, double imag);

//libero el complejo del heap
void freeComplex(complexADT numero);

double real(complexADT numero);

double imag(complexADT numero);

complexADT sumaComplex(complexADT numero1, complexADT numero2);

complexADT restaComplex(complexADT numero1, complexADT numero2);

complexADT multComplex(complexADT numero1, complexADT numero2);

complexADT divComplex(complexADT numero1, complexADT numero2);

complexADT conjuComplex(complexADT numero);

#endif

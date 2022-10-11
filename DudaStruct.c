//Duda sobre: asignación de dos estructuras
//Pido perdón por los magic numbers

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//CASO 1

typedef struct{
  int x;
  int y;
} Point;

//CASO 2

typedef struct{
  char name[50];
  char id[10];
  int age;
  int grades[5];
} Student;

//CASO 3

typedef struct{
  int *array;
} Data;

int main(void){
  
  //CASO 1: Estructura sin arrays ni punteros (En este caso son ints)
  
  Point p1 = {5, 10};
  
  Point p2 = 
    { 
      .y = 8, 
      .x = 2
    };
  
  p1 = p2;
  
  //Se copian los datos normalmente, miembro por miembro, del struct p2 al struct p1
  
  //--------------------------------------------------------------------------------------

  //CASO 2: Estructura sin punteros pero con arrays
  
  //Podés ignorar las declaraciones
  Student kevin, john;
  
  strcpy(kevin.name, "Kevin");
  strcpy(kevin.id, "000123123");
  kevin.age = 40;
  kevin.grades[0] = 1;
  kevin.grades[1] = 2;
  kevin.grades[2] = 3;
  kevin.grades[3] = 4;
  kevin.grades[4] = 5;
  
  strcpy(john.name, "John");
  strcpy(john.id, "123123000");
  john.age = 20;
  john.grades[0] = 10;
  john.grades[1] = 9;
  john.grades[2] = 8;
  john.grades[3] = 7;
  john.grades[4] = 6;

  kevin = john;
  
  //Se copian los datos normalmente, índice por índice de cada array, del struct john al struct kevin

  //--------------------------------------------------------------------------------------
  
  //CASO 3: Estructura con punteros dinámicos

  // Data p1 y Data p2 contienen un único puntero llamado array
  Data p1;
  Data p2;

  p1.array = malloc(sizeof(int) * 5); //o podría usar p1.(*array) en lugar de int
  p2.array = malloc(sizeof(int) * 5);

  //Podés ignorar las declaraciones 
  p1.array[0] = 1;
  p1.array[1] = 2;
  p1.array[2] = 3;
  p1.array[3] = 4;
  p1.array[4] = 5;

  p2.array[0] = 9;
  p2.array[1] = 9;
  p2.array[2] = 9;
  p2.array[3] = 9;
  p2.array[4] = 9;

  p1 = p2;

  /*
  
  Duda:

  En este caso el puntero dentro de p1 apuntará a dónde apunta el puntero de p2? De ser así, la memoria que reservé para p1
  seguirá "perdida" en el heap? 

  */

  return 0;
}

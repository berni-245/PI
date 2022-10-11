//Duda sobre: asignación de dos estructuras
//Pido perdón por los magic numbers

#include <stdlib.h>

typedef struct{
  int x;
  int y;
} Point;

typedef struct{
  int *array;
} Data;

int main(void){
  
  //Estructura sin arrays ni punteros (En este caso son ints)
  
  Point p1 = {5, 10};
  
  Point p2 = {.y = 8, .x = 2};
  
  p1 = p2;
  
  //Se copian los datos normalmente, miembro por miembro, del struct p2 al struct p1
  //Nota: con arrays estáticos me funcionó también
  
  //--------------------------------------------------------------------------------------
  
  //Estructura con arrays dinámicos

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

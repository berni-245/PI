#ifndef _DICCIOADT__H
#define _DICCIOADT__H
#define MAXWIDTH 25
#define MAXSIGNIFICADO 255
typedef struct diccioCDT *diccioADT;
typedef int (*compare) (const char * a, const char * b);
/*--------------------------------------------------------------
* Operaciones disponibles sobre el TAD
* ------------------------------------------------------------*/
diccioADT creaDiccionario(compare cmp);
void liberaDiccionario(diccioADT dic);
int agregaPalabra(diccioADT dic, char* palabra, char* significado);
int existePalabra(diccioADT dic, char* palabra);
int actualizaSignificado(diccioADT dic, char* palabra, char* significado);
int copiaSignificado(diccioADT dic, char* palabra, char* significado);
void imprimeDiccionario(diccioADT dic);
int borraPalabra(diccioADT dic, char* palabra);
int grabaDiccionario(diccioADT dic, char *archivo);
int leeDiccionario(diccioADT dic, char *archivo);

#endif // _DICCIOADT__H

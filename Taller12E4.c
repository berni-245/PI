#include "E4.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define BLOQUE 10
#define LETRAS 26

typedef struct palSign{
    char * pal;
    char * sign;
}palSign;

typedef struct listaPalabra{
    int cant;
    int size;
    palSign * lista;
}listaPalabra;

typedef struct diccioCDT{
    listaPalabra inicial[LETRAS];
    compare cmp;
}diccioCDT;

diccioADT creaDiccionario(compare cmp){
    diccioADT aux = malloc(sizeof(*aux));
    int i;

    for(i=0; i < LETRAS;  i++){
        aux->inicial[i].cant = 0;
        aux->inicial[i].size = 0;
        aux->inicial[i].lista = NULL;
    }

    aux->cmp = cmp;

    return aux;
}

void
liberaDiccionario(diccioADT dic){
    int i, j;
    for(i=0; i<LETRAS; i++){
        for(j=0; j < dic->inicial[i].size; j++){
            free(dic->inicial[i].lista[j].pal);
            free(dic->inicial[i].lista[j].sign);
        }
        free(dic->inicial[i].lista);
    }
    free(dic);   
}

int
isPalabra(char * palabra){
    int i, flag = 1;
    for(i=0; palabra[i] != 0 && flag; i++){
        if(!isalpha(palabra[0]) && !isspace(palabra[0]))
            flag = 0;
    }
    return flag;
}

palSign *
checkEspacio(palSign * lista, int cant, int * size){
    if(*size == cant){
            *size = *size + BLOQUE;
            palSign * aux = realloc(lista, sizeof(*aux)*(*size));
            return aux;
        }
    return lista;
}

static int
ubicaPalabra(palSign * lista, char * palabra, int dim, compare cmp){
    int i, flag = 0;
    for(i=0; i<dim && !flag; i++){
        if(cmp(lista[i].pal, palabra)==0)
            flag = 1;
    }
    return flag;
}


int
existePalabra(diccioADT dic, char * palabra){
    char letra = tolower(*palabra) - 'a';
    return ubicaPalabra(dic->inicial[letra].lista, palabra, dic->inicial[letra].cant, dic->cmp);
}
int
buscarIndicePalabra(palSign * lista, char * palabra, int dim, compare cmp){
    int i, flag = 0;
     for(i=0; i<dim && !flag; i++){
        if(cmp(lista[i].pal, palabra)==0)
            flag = 1;
    }

    if(flag)
        return i-1;

    return -1;
    
}


int
agregaPalabra(diccioADT dic, char * palabra, char * significado){
    int flag = 0;
    if(isPalabra(palabra) && isPalabra(significado)){
        char letra = tolower(*palabra) - 'a';
        int dim = dic->inicial[letra].cant;
        int len1 = strlen(palabra);
        int len2 = strlen(significado);
        if(!ubicaPalabra(dic->inicial[letra].lista, palabra, dim, dic->cmp) && len1 <= MAXWIDTH && len2 <= MAXSIGNIFICADO){
            dic->inicial[letra].lista = checkEspacio(dic->inicial[letra].lista, dim, &dic->inicial[letra].size); 
            //checkeo si tengo espacio

            dic->inicial[letra].lista[dim].pal = malloc(sizeof(char)*(MAXWIDTH+1));
            dic->inicial[letra].lista[dim].pal = strcpy(dic->inicial[letra].lista[dim].pal, palabra);
            dic->inicial[letra].lista[dim].sign = malloc(sizeof(char)*(MAXSIGNIFICADO+1));
            dic->inicial[letra].lista[dim].sign = strcpy(dic->inicial[letra].lista[dim].sign, significado);

            dic->inicial[letra].cant = ++dim;

            flag = 1;
        }
    }

    return flag;
}

int
actualizaSignificado(diccioADT dic, char * palabra, char * significado){
    int flag = 0;
    if(isPalabra(palabra) && isPalabra(significado)){
        char letra = tolower(*palabra) - 'a';
        int len = strlen(significado);
        int dim = dic->inicial[letra].cant;
        int indice;
        if(len <= MAXSIGNIFICADO && (indice = buscarIndicePalabra(dic->inicial[letra].lista, palabra, dim, dic->cmp)) != -1){
            dic->inicial[letra].lista[indice].sign = strcpy(dic->inicial[letra].lista[indice].sign, significado);

            flag = 1;
        }
    }

    return flag;

}

void
imprimeDiccionario(diccioADT dic){
    int i, j;
    for(i=0; i<LETRAS; i++){
        for(j=0; j < dic->inicial[i].size; j++){
            printf("Palabra: %s\n", dic->inicial[i].lista[j].pal);
            printf("Significado: %s\n",dic->inicial[i].lista[j].sign);
        }
        
    }
}

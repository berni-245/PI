#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "E17.h"
#define BLOQUE 50

typedef struct node{
    int clave;
    char * frase;
    int dimFrase;
    struct node * tail;
}node;

typedef struct phrasesCDT{
    node * first;
    int dim;
    int from; //la clave mínima
    int to; //la clave máxima
}phrasesCDT;

phrasesADT
newPhrasesADT(size_t keyFrom, size_t keyTo){
    phrasesADT aux;
    if((int)keyTo - (int)keyFrom >= 0){    
        aux = malloc(sizeof(*aux));
        aux->first = NULL;
        aux->dim = 0;
        aux->from = keyFrom;
        aux->to = keyTo;
    }
    else{
        aux = NULL;
    }
    return aux;
}

static void
freePhrasesRec(node * list){
    if(list == NULL)
        return;

    node * aux = list->tail;
    free(list->frase);
    free(list);
    freePhrasesRec(aux);

}

void
freePhrases(phrasesADT ph){
    freePhrasesRec(ph->first);
    free(ph);
}

static char *
agregarFrase(const char * phrase, int * newDim){
    char * aux = NULL;
    int i;
    for(i=0; phrase[i] != '\0'; i++){
        if(i%BLOQUE == 0){
            aux = realloc(aux, (i+BLOQUE)*sizeof(*aux));
        }
        aux[i] = phrase[i];
    }
    aux = realloc(aux, (i+1)*sizeof(*aux));
    aux[i] = 0;
    *newDim = i;

    return aux;
}

static node *
putRec(node * list, int key, const char * phrase, int * flagDim){
    if(list == NULL || list->clave > key){
        node * aux = malloc(sizeof(*aux));
        aux->frase = agregarFrase(phrase, &aux->dimFrase);
        aux->clave = key;
        aux->tail = list;
        *flagDim = 1;


        return aux;
    }

    if(list->clave == key){
        free(list->frase);
        list->frase = agregarFrase(phrase, &list->dimFrase);

        return list;
    }

    list->tail = putRec(list->tail, key, phrase, flagDim);

    return list;
}

int
put(phrasesADT ph, size_t key, const char * phrase){
    int flag = 0;
    if(key >= ph->from && key <= ph->to){
        int flagDim = 0;
        ph->first = putRec(ph->first, key, phrase, &flagDim);
        flag = 1;
        ph->dim += flagDim;
    }

    return flag;
}

static char * 
getRec(node * list, int key){
    if(list == NULL || list->clave > key){
        return NULL;
    }
    if(list->clave == key){
        char * aux = malloc((list->dimFrase+1)*sizeof(*aux));
        strcpy(aux, list->frase);
        aux[list->dimFrase] = 0;

        return aux;
    }

    return getRec(list->tail, key);

}

char *
get(const phrasesADT ph, size_t key){
    if(key >= ph->from && key <= ph->to){
        return getRec(ph->first, key);
    }

    return NULL;
}

size_t
size(const phrasesADT ph){
    return ph->dim;
}

static int
checkearRangoConcat(int fromOrig, int toOrig, int fromNew, int toNew){
    return fromOrig <= fromNew && fromNew <= toOrig && fromOrig <= toNew && toNew <= toOrig && (toNew - fromNew) >= 0;
}

//si no tiene inicio en el rango, retorna NULL
static node *
hallarInicio(node * list, int from, int to){
    if(list == NULL || list->clave > to)
        return NULL;
    if(from <= list->clave && list->clave <= to)
        return list;

    return hallarInicio(list->tail, from, to);
}

static char *
concatAux(node * list, int from, int to){
    char * aux;
    list = hallarInicio(list, from, to);
    if(list != NULL){
        aux = malloc((list->dimFrase+1)*sizeof(*aux));
        strcpy(aux, list->frase);
        int dim = list->dimFrase;
        list = list->tail;

        while(list != NULL && list->clave <= to){
            dim += list->dimFrase;
            aux = realloc(aux, (dim+1)*sizeof(*aux));
            strcat(aux, list->frase);
            list = list->tail;
        }
    }
    else{
        aux = calloc(1,sizeof(*aux));
    }

    return aux;
}

char *
concat(const phrasesADT ph, size_t from, size_t to){
    if(checkearRangoConcat(ph->from, ph->to, from, to)){
        return concatAux(ph->first, from, to);
    }
    return NULL;
}


char *
concatAll(const phrasesADT ph){
    return concat(ph, ph->from, ph->to);
}

//En el tp cambiaría varios ints por size_t
#include <stdlib.h>
#include <stdio.h>
#include "E14.h"

typedef struct node{
    elemType elem;
    struct node * tail;
}node;

typedef struct listCDT{
    node * firstAsc;
    node * nextAsc;
    node * firstInser;
    node * nextInser;
    node * lastInser;
    int dim; 
    compare cmp;
}listCDT;

listADT
newList(compare cmp){
    listADT aux = calloc(1, sizeof(*aux));
    aux->cmp = cmp;
    return aux;
}

static node *
addAsc(node * first, elemType elem, compare cmp, int * flag){
    short c;
    if(first == NULL || (c = cmp(first->elem, elem)) > 0){
        node * asc = malloc(sizeof(*asc));
        asc->elem = elem;
        asc->tail = first;
        *flag = 1;
        return asc;
    }
    if(c == 0){
        return first;
    }

    first->tail = addAsc(first->tail, elem, cmp, flag);

    return first;

}

void
add(listADT list, elemType elem){

    node * inser = malloc(sizeof(*inser));

    if(list->firstAsc == NULL){
        node * asc = malloc(sizeof(*asc));

        asc->elem = elem;
        inser->elem = elem;
        asc->tail = NULL;
        inser->tail = NULL;
        

        list->firstAsc = asc;

        list->firstInser = inser;
        list->lastInser = inser;

        return;
    }

    int flag = 0;

    list->firstAsc = addAsc(list->firstAsc, elem, list->cmp, &flag);

    if(flag){
        inser->elem = elem;
        inser->tail = NULL;
        list->lastInser->tail = inser;
        list->lastInser = inser;
        (list->dim)++;
    }
    
    return;   
}

void
toBegin(listADT list){
    list->nextInser = list->firstInser;
}

int
hasNext(listADT list){
    if(list->nextInser == NULL){
        return 0;
    }
    return 1;
}

elemType
next(listADT list){
    if(!hasNext(list)){
        puts("No hay siguiente!");
        exit(1);
    }

    elemType aux = list->nextInser->elem;
    list->nextInser = list->nextInser->tail;
    return aux;

}

void
toBeginAsc(listADT list){
    list->nextAsc = list->firstAsc;
}

int
hasNextAsc(listADT list){
    if(list->nextAsc == NULL){
        return 0;
    }

    return 1;
}

elemType nextAsc(listADT list){
    if(!hasNextAsc(list)){
        puts("NO tiene next");
        exit(1);
    } 

    elemType aux = list->nextAsc->elem;
    list->nextAsc = list->nextAsc->tail;
    return aux;
}

void
freeLista(node * asc){
    if(asc == NULL)
        return;
    node * aux = asc->tail;
    free(asc);
    freeLista(aux);
}

void
freeList(listADT list){
    freeLista(list->firstAsc);
    freeLista(list->firstInser);

    free(list);
}
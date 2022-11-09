#include <stdlib.h>
#include <stdio.h>
#include "E15.h"

typedef struct node{
    elemType elem;
    struct node * tail;
}node;

typedef struct moveToFrontCDT{
    node * first;
    node * next; //para el iterador, el actual
    node * last; //ultimo de la lista
    int size;
    compare cmp; 

}moveToFrontCDT;

moveToFrontADT
newMoveToFront(compare cmp){
    moveToFrontADT aux = calloc(1, sizeof(*aux));
    aux->cmp = cmp;
    return aux;
}

static void
freeList(node * list){
    if(list == NULL)
        return;
    
    node * aux = list->tail;
    free(list);
    freeList(aux);
}

void
freeMoveToFront(moveToFrontADT m){
    freeList(m->first);
    free(m);
}

unsigned int
size(moveToFrontADT moveToFront){
    return moveToFront->size;
}

//Si no encuentra el elemento, retorna NULL
//Si lo encuentra el flag queda 1 y retorna la dirección de dónde se encuentra
static node *
buscarPosElem(node * list, elemType elem, compare cmp){
    node * aux = NULL;
    int flag = 0;
    while(list != NULL && !(flag)){
        if(cmp(list->elem, elem)==0){
            aux = list;
            flag = 1;
        }
        list = list->tail;
    }

    return aux;

}

unsigned int
add(moveToFrontADT moveToFront, elemType elem){
    int flag = 0;

    node * flagP = buscarPosElem(moveToFront->first, elem, moveToFront->cmp);
    if(flagP != NULL)
        return flag;

    node * aux = malloc(sizeof(*aux));
    aux->elem = elem;
    aux->tail = NULL;

    if(moveToFront->first == NULL){

        moveToFront->first = aux;
        moveToFront->last = aux;

    }
    else{
        moveToFront->last->tail = aux;
        moveToFront->last = aux;
    }
    flag = 1;
    (moveToFront->size)++;

    return flag;
}

void
toBegin(moveToFrontADT moveToFront){
    moveToFront->next = moveToFront->first;
}

int
hasNext(moveToFrontADT moveToFront){
    if(moveToFront->next == NULL)
        return 0;

    return 1;
}

elemType
next(moveToFrontADT moveToFront){
    if(!hasNext(moveToFront)){
        puts("No tiene otro elemento!");
        exit(1);
    }

    elemType aux = moveToFront->next->elem;
    moveToFront->next = moveToFront->next->tail;
    return aux;
}

elemType *
get(moveToFrontADT moveToFront, elemType elem){
    node * aux = buscarPosElem(moveToFront->first, elem, moveToFront->cmp);
    if(aux == NULL)
        return NULL;

    elemType * resp = malloc(sizeof(*resp));
    resp[0] = aux->elem;

    elemType auxElem = moveToFront->first->elem;
    moveToFront->first->elem = aux->elem;
    aux->elem = auxElem;

    return resp;
}

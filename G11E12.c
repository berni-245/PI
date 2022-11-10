#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "E12.h"

typedef struct node2{
    char nombre[LONG_PALABRAS+1];
    struct node2 * tail;
}node2;

typedef struct node{
    char nombre[LONG_PALABRAS+1];
    int dimAlegados;
    node2 * alegados;
    struct node * tail;

}node;

typedef struct socialCDT{
    node * first;
    int dim;
}socialCDT;

socialADT newSocial(){
    return calloc(1, sizeof(socialCDT));
}

static void
freeSocialRec2(node2 * alegados, int dim){
    if(dim == 0)
        return;
    
    node2 * aux = alegados->tail;
    free(alegados);
    freeSocialRec2(aux, dim-1);
}

static void
freeSocialRec(node * personas, int dim){
    if(dim == 0)
        return;
    
    node * aux = personas->tail;
    freeSocialRec2(personas->alegados, personas->dimAlegados);
    free(personas);
    freeSocialRec(aux, dim-1);
}

void
freeSocial(socialADT soc){
    freeSocialRec(soc->first, soc->dim);
    free(soc);
}

static node *
addPersonRec(node * personas, int * dim, const char * name){
    if(personas == NULL || strcmp(personas->nombre, name) > 0){
        node * aux = malloc(sizeof(*aux));
        strcpy(aux->nombre, name);
        aux->dimAlegados = 0;
        aux->tail = personas;
        aux->alegados = NULL;
        (*dim)++;
        
        return aux;

    }

    if(strcmp(personas->nombre, name) == 0)
        return personas;

    personas->tail = addPersonRec(personas->tail, dim, name);

    return personas;
}

void
addPerson(socialADT soc, const char * name){
    soc->first = addPersonRec(soc->first, &soc->dim, name);
}

static node2 *
addRelatedRec2(node2 * alegados, const char * related){
    if(alegados == NULL || strcmp(alegados->nombre, related) >= 0){
        node2 * aux = malloc(sizeof(*aux));
        strcpy(aux->nombre, related);
        aux->tail = alegados;

        return aux;
    }

    alegados->tail = addRelatedRec2(alegados->tail, related);

    return alegados;
}


static void
addRelatedRec(node * personas, const char * name, const char * related){
    if(personas == NULL || strcmp(personas->nombre, name) > 0){
        return;
    }

    if(strcmp(personas->nombre, name) == 0){
        personas->alegados = addRelatedRec2(personas->alegados, related);
        (personas->dimAlegados)++;

    }

    addRelatedRec(personas->tail, name, related);
}

void
addRelated(socialADT soc, const char * name, const char * related){
    addRelatedRec(soc->first, name, related);
}

static void
personsRec(node * persons, char * respuesta[], int dim){
    int i;
    for(i=0; i<dim; i++){
        respuesta[i] = malloc((LONG_PALABRAS+1)*sizeof(char));
        strcpy(respuesta[i], persons->nombre);
        persons = persons->tail;
    }
    respuesta[i] = NULL;
}

char ** persons(const socialADT soc){
    char ** aux = malloc((soc->dim+1)*sizeof(char *));

    personsRec(soc->first, aux, soc->dim);

    return aux;
}

static void
relatedRec2(node2 * alegados, char * resp[], int dim){
    int i;

    for(i=0; i<dim; i++){
        resp[i] = malloc((LONG_PALABRAS+1)*sizeof(char));
        strcpy(resp[i], alegados->nombre);
        alegados = alegados->tail;
    }
    resp[i] = NULL;

}

static char **
relatedRec(node * personas, const char * person){
    if(personas == NULL || strcmp(personas->nombre, person) > 0){
        char ** aux  = malloc(sizeof(char *));
        aux[0] = NULL;
        return aux;
    }

    if(strcmp(personas->nombre, person) == 0){
        char ** resp = malloc((personas->dimAlegados+1)*sizeof(char *));
        relatedRec2(personas->alegados, resp, personas->dimAlegados);
        return resp;
    }

    return relatedRec(personas->tail, person);
}

char ** related(const socialADT soc, const char * person){
    return relatedRec(soc->first, person);
}

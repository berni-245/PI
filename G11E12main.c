#include "E12.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

int main(void) {
	socialADT soc = newSocial();
	char ** rel;
	rel = persons(soc); // rel = {NULL}
	free(rel);
	rel = related(soc, "carlitos"); // rel = {NULL};
	free(rel);
	char aux[30] = "juan";
	addPerson(soc, aux); // soc contiene a "juan"
	strcpy(aux,"luisa");
	addPerson(soc, aux); // soc contiene a "juan" y "luisa"
	strcpy(aux,"ana");
	addRelated(soc, "juan", "pedro");
	addRelated(soc, "juan", aux);
	addRelated(soc, "juan", "juana");
	char ** juanFriends = related(soc, "juan");
	// juanFriends es {"ana", "juana", "pedro", NULL};
	for(int i=0; juanFriends[i] != NULL; i++)
	free(juanFriends[i]);
	free(juanFriends);
	addPerson(soc, "andres");
	addPerson(soc, "analia");
	char **p = persons(soc);
	// p={"analia","andres","juan","luisa",NULL}
	for(int i=0; p[i] != NULL; i++)
	free(p[i]);
	free(p);
	addRelated(soc, "juan", "john");
	// Ahora los amigos de juan son "ana", "john", "juana" y "pedro"
	freeSocial(soc);
	puts("OK!");
	return 0;
}

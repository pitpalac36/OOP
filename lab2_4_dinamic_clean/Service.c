#include "Service.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>

DynamicArray createList()
{
	return createEmpty();
}

void destroyList(DynamicArray* c)
{
	destroy(c);
}

int addParticipant(DynamicArray* c, char* nume, char* prenume, int scor)
{
	Participant p = creeazaParticipant(nume, prenume, scor);
	int eroare = valideaza(p);
	if (eroare != 0) {
		distrugeParticipant(&p);
		return eroare;
	}
	insert(c, p);
	return 0;
}

void removeAll(DynamicArray* c)
{
	deleteAll(c);
}

int updateOne(DynamicArray* c, char* nume, char* prenume, int scorNou)
{
	if (scorNou < 0)
		return 1;
	else {
		if (getBy(c, nume, prenume) == NULL)
			return 2;
		actualizeazaRepo(c, nume, prenume, scorNou);
		return 0;
	}
}


DynamicArray filtreaza(DynamicArray lista, char* substr)
{
	DynamicArray filtered = createEmpty();
	for (int i = 0; i < lista.size; i++) {
		Participant p = get(&lista, i);
		if (strstr(p.nume, substr) != NULL)
			insert(&filtered, creeazaParticipant(p.nume, p.prenume, p.scor));
	}
	return filtered;
}

int dimensiune(DynamicArray c) {
	return length(c);
}


void testAdaugareStergereActualizareFiltrare() {

	DynamicArray lista = createList();
	int error = addParticipant(&lista, "", "", -20);
	assert(error == 1);
	assert(dimensiune(lista) == 0);
	error = addParticipant(&lista, "pop", "", 4000);
	assert(error == 2);
	assert(dimensiune(lista) == 0);
	error = addParticipant(&lista, "alesu", "alexandra", 100);
	assert(error == 0);
	assert(dimensiune(lista) == 1);
	addParticipant(&lista, "sdf", "werg", 1230);
	updateOne(&lista, "alesu", "alexandra", 2000);
	assert(dimensiune(lista) == 2);
	int sc1 = getScor(&lista, 0);
	assert(sc1 == 2000);
	assert(updateOne(&lista, "alesu", "alexandra", -123) == 1);
	updateOne(&lista, "alesu", "constantina", 123);
	DynamicArray filtered = filtreaza(lista, "a");
	assert(dimensiune(lista) == 2);
	assert(length(filtered) == 1);
	assert(strcmp(filtered.elems[0].nume, "alesu") == 0);
	destroyList(&lista);
	removeAll(&filtered);
	destroyList(&filtered);
}
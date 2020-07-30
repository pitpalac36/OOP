#include "Service.h"
#include <assert.h>
#include <stdio.h>

int adaugaService(List* lista, char* nume, char* prenume, int scor)
{
	Participant p = creeazaParticipant(nume, prenume, scor);
	int deReturnat = valideaza(p);
	if (deReturnat == 0) {
		adauga(lista, p);
		return 0;
	}
	return deReturnat;
}


int actualizeazaService(List* lista, char* nume, char* prenume, int scorNou)
{
	if (scorNou < 0)
		return 1;
	else {
		if (getBy(lista, nume, prenume) == NULL)
			return 2;
		actualizeazaRepo(lista, nume, prenume, scorNou);
		return 0;
	}
}


void stergeToti(List* lista)
{
	for (int i = 0; i < dimensiune(lista); i++)
		distrugeParticipant(&lista->elems[i]);
	distrugeLista(&lista);
}


List filtreaza(List lista, char* substr)
{
	List sub = creeazaGoala();
	for (int i = 0; i < dimensiune(&lista); i++) {
		Participant p = get(&lista, i);
		if (strstr(p.nume, substr) != NULL)
			adauga(&sub, p);
	}
	return sub;
}


void testAdaugareStergereActualizareFiltrare() {
	List lista = creeazaGoala();
	int error = adaugaService(&lista, "", "", -20);
	assert(error == 1);
	assert(dimensiune(&lista) == 0);

	error = adaugaService(&lista, "pop", "", 4000);
	assert(error == 2);
	assert(dimensiune(&lista) == 0);

	error = adaugaService(&lista, "alesu", "alexandra", 1000);

	assert(error == 0);
	assert(dimensiune(&lista) == 1);
	actualizeazaService(&lista, "alesu", "alexandra", 2000);
	assert(dimensiune(&lista) == 1);

	int sc1 = lista.elems[0].scor;
	assert(sc1 == 2000);
	List filtered = filtreaza(lista, "a");
	assert(dimensiune(&lista) == 1);
	assert(dimensiune(&filtered) == 1);
	assert(strcmp(filtered.elems[0].nume, "alesu") == 0);
}
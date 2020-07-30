#include "Repo.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>


List creeazaGoala()
{
	List lista;
	lista.lungime = 0;
	return lista;
}


void distrugeLista(List* list)
{
	list->lungime = 0;
}

void actualizeazaRepo(List* lista, char* nume, char* prenume, int scorNou)
{
	Participant* p = getBy(lista,nume, prenume);
	if (p != NULL) {
		setScor(p, scorNou);
	}
	
}

bool egali(ElemType* p1, ElemType* p2)
{
	return (strcmp(*p1->nume, *p2->nume) == 0 && strcmp(*p1->prenume, *p2->prenume) == 0);
}

int dimensiune(List* lista)
{
	return lista->lungime;
}


ElemType get(List* lista, int poz)
{
	return lista->elems[poz];
}

ElemType* getBy(List* lista, char* nume, char* prenume)
{
	for (int i = 0; i < dimensiune(lista); i++)
		if (strcmp(lista->elems[i].nume, nume) == 0)
			if (strcmp(lista->elems[i].prenume, prenume) == 0) {
				return &(lista->elems[i]);
			}
	return NULL;
}


void adauga(List* lista, ElemType elem)
{
	lista->elems[lista->lungime] = elem;
	lista->lungime++;
}

void testCreeazaLista()
{
	List lista = creeazaGoala();
	assert(dimensiune(&lista) == 0);
}

void testItereazaLista()
{
	List lista = creeazaGoala();
	adauga(&lista, creeazaParticipant("ana", "ana", 300));
	adauga(&lista, creeazaParticipant("ionescu", "ionel", 500));
	assert(dimensiune(&lista) == 2);
	assert(getBy(&lista, "ana", "ana") != NULL);
	assert(getBy(&lista, "z", "x") == NULL);
	Participant p = get(&lista, 0);
	assert(strcmp(p.nume, "ana") == 0);
	p = get(&lista, 1);
	assert(p.scor == 500);
	distrugeParticipant(&p);
	distrugeLista(&lista);
	assert(dimensiune(&lista) == 0);
}

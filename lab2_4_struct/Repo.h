#pragma once
#include "participant.h"
typedef Participant ElemType;

typedef struct {
	ElemType elems[50];
	int lungime;
}List;


/*
 creeaza o lista vida
*/
List creeazaGoala();


/*
 elibereaza spatiul din memorie alocat listei date ca parametru
*/
void distrugeLista(List* list);

void actualizeazaRepo(List* lista, char* nume, char* prenume, int scorNou);


/*
 returneaza nr de elemente din lista
*/
int dimensiune(List* lista);


/*
 returneaza elementul de pe o pozitie specificata
*/
ElemType get(List* lista, int poz);


ElemType* getBy(List* lista, char* nume, char* prenume);


bool egali(ElemType* p1, ElemType* p2);

/*
 adauga un Elem in lista
*/
void adauga(List* lista, ElemType elem);


void testCreeazaLista();


void testItereazaLista();
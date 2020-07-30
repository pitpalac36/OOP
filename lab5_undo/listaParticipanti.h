#pragma once
#include "participant.h"

typedef void* TElem;

/*
 functie pt distrugerea unui TElem
*/
typedef void(*DestroyFct) (TElem);


/*
  functie pt copierea unui TElem
*/
typedef TElem(*CopyFct) (TElem);


typedef struct
{
	TElem* elemente;
	int lungime;
	int capacitate;
	DestroyFct dfct;
}listaParticipanti;

/*
	Functia creeaza o lista de tip listaParticipanti.
	input: -
	output: lista - obiect de tip listaParticipanti
*/
listaParticipanti* creeazaListaGoala(DestroyFct dfct);

/*
	Functia distruge o lista de tip listaParticipanti.
	input: l - obiect de tip listaParticipanti
	output: -
*/
void distrugeLista(listaParticipanti* l);

/*
	Functia returneaza lungimea listei transmisa prin parametru.
	input: l - obiect de tip listaParticipanti
	output: lungimea listei - numar intreg
*/
int lungimeLista(listaParticipanti* l);

/*
	Functia returneaza un obiect de tip TElem aflat pe o anumita pozitie
	(transmisa prin parametru) in lista.
	input: l       - obiect de tip listaParticipanti
		   pozitie - numar intreg
	output: obiect de tip TElem
*/
TElem* getElement(listaParticipanti* l, int pozitie);

/*
	Functia adauga un obiect de tip TElem in lista de participanti.
	input: l    - obiect de tip listaParticipanti
		   elem - obiect de tip TElem
	output: -
*/
void adaugaElement(listaParticipanti* l, TElem elem);

/*
	Functia face o copie la o lista de tip listaParticipanti.
	input:  l     - obiect de tip listaParticipanti
	output: lista - obiect de tip listaParticipanti
					(copie a listei transmisa prin parametru)
*/
listaParticipanti* copiazaLista(listaParticipanti* l, CopyFct f);

/*
	Functia mareste numarul de elemente pe care lista de participanti le poate memora.
	input: l  - obiect de tip listaParticipanti
	output: 0 - inca mai este loc
			1 - s-a facut resize
*/
int maresteCapacitateListaParticipanti(listaParticipanti* l);

TElem stergeUltim(listaParticipanti* l);

void testCreeazaListaGoala();
void testDistrugeLista();
void testLungimeLista();
void testGetElement();
void testAdaugaElement();
void testCopiazaLista();
void testMaresteCapacitateListaParticipanti();
void testStergeUltim();
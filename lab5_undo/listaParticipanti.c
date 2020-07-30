#include "listaParticipanti.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>

/*
	Functia creeaza o lista de tip listaParticipanti.
	input: -
	output: lista - obiect de tip listaParticipanti
*/
listaParticipanti* creeazaListaGoala(DestroyFct dfct)
{
	listaParticipanti* lista = malloc(sizeof(listaParticipanti));
	lista->dfct = dfct;
	lista->elemente = malloc(sizeof(TElem) * 100);
	lista->lungime = 0;
	lista->capacitate = 100;
	return lista;
}

/*
	Functia distruge o lista de tip listaParticipanti.
	input: l - obiect de tip listaParticipanti
	output: -
*/
void distrugeLista(listaParticipanti* l)
{
	for (int i = 0; i < l->lungime; i++)
		l->dfct(l->elemente[i]);
	free(l->elemente);
	free(l);
}

/*
	Functia returneaza lungimea listei transmisa prin parametru.
	input: l - obiect de tip listaParticipanti
	output: lungimea listei - numar intreg
*/
int lungimeLista(listaParticipanti* l)
{
	return l->lungime;
}

/*
	Functia returneaza un obiect de tip TElem aflat pe o anumita pozitie 
	(transmisa prin parametru) in lista.
	input: l       - obiect de tip listaParticipanti
	       pozitie - numar intreg
	output: obiect de tip TElem
*/
TElem* getElement(listaParticipanti* l, int pozitie)
{
	return l->elemente[pozitie];
}

/*
	Functia adauga un obiect de tip TElem in lista de participanti.
	input: l    - obiect de tip listaParticipanti
		   elem - obiect de tip TElem
	output: -
*/
void adaugaElement(listaParticipanti* l, TElem elem)
{
	l->elemente[l->lungime] = elem;
	l->lungime++;
}

/*
	Functia face o copie la o lista de tip listaParticipanti.
	input:  l     - obiect de tip listaParticipanti
	output: lista - obiect de tip listaParticipanti 
	                (copie a listei transmisa prin parametru)
*/
listaParticipanti* copiazaLista(listaParticipanti* l, CopyFct cp)
{
	listaParticipanti* lista = creeazaListaGoala(l->dfct);
	for (int i = 0; i < l->lungime; i++)
	{
		TElem p = getElement(l, i);
		adaugaElement(lista, cp(p));
	}
	return lista;
}

/*
	Functia mareste numarul de elemente pe care lista de participanti le poate memora.
	input: l  - obiect de tip listaParticipanti
	output: 0 - inca mai este loc
	        1 - s-a facut resize
*/
int maresteCapacitateListaParticipanti(listaParticipanti* l)
{
	if (l->lungime < l->capacitate)
		return 0;
	int nCap = 2 * l->capacitate;
	TElem* elemente = malloc(sizeof(TElem) * nCap);
	for (int i = 0; i < l->lungime; i++)
		elemente[i] = l->elemente[i];
	free(l->elemente);
	l->elemente = elemente;
	l->capacitate = nCap;
	return 1;
}



TElem stergeUltim(listaParticipanti* l) {
	TElem rez = l->elemente[l->lungime - 1];
	l->lungime -= 1;
	return rez;
}



void testCreeazaListaGoala()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	assert(l->lungime == 0);
	distrugeLista(l);
}

void testDistrugeLista()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	adaugaElement(l, p);
	assert(lungimeLista(l) == 1);
	distrugeLista(l);
}

void testLungimeLista()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	adaugaElement(l, p);
	assert(lungimeLista(l) == 1);

	distrugeLista(l);
}

void testGetElement()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	adaugaElement(l, p);
	Participant* el = (Participant*)getElement(l, 0);
	assert(strcmp(getNume(el), getNume(p)) == 0);
	assert(strcmp(getPrenume(el), getPrenume(p)) == 0);
	assert(getScor(el) == getScor(p));

	distrugeLista(l);
}

void testAdaugaElement()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	adaugaElement(l, p);
	assert(lungimeLista(l) == 1);

	distrugeLista(l);
}

void testCopiazaLista()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	TElem elem1 = creeazaParticipant("Pop", "Mihai", 100);
	TElem elem2 = creeazaParticipant("Vasile", "Vasilescu", 99);
	adaugaElement(l, elem1);
	adaugaElement(l, elem2);
	listaParticipanti* copie = copiazaLista(l,copiazaParticipant);
	assert(l->lungime == copie->lungime);
	for (int i = 0; i < l->lungime; i++)
	{
		assert(strcmp(getNume(l->elemente[i]), getNume(copie->elemente[i])) == 0);
		assert(strcmp(getPrenume(l->elemente[i]), getPrenume(copie->elemente[i])) == 0);
		assert(getScor(l->elemente[i]) == getScor(copie->elemente[i]));
	}
	distrugeLista(copie);
	distrugeLista(l);
}

void testMaresteCapacitateListaParticipanti()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	TElem elem1 = creeazaParticipant("Pop", "Mihai", 100);
	char litere[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	adaugaElement(l, elem1);
	assert(maresteCapacitateListaParticipanti(l) == 0);
	for (int i = 0; i <= 100; i++)
	{
		maresteCapacitateListaParticipanti(l);
		char nume[2];
		nume[0] = litere[rand() % 26];
		nume[1] = '\0';
		TElem elem2 = creeazaParticipant(nume, "Mihai", 100);
		adaugaElement(l, elem2);
	}
	assert(l->capacitate == 200);
	distrugeLista(l);
}

void testStergeUltim()
{
	listaParticipanti* l = creeazaListaGoala(distrugeParticipant);
	Participant* p = creeazaParticipant("Pop", "Mirela", 100);
	adaugaElement(l, p);
	assert(lungimeLista(l) == 1);
	stergeUltim(l);
	assert(lungimeLista(l) == 0);
	distrugeParticipant(p);
	distrugeLista(l);
}

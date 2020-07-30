#include "serviceParticipant.h"
#include <stdlib.h>
#include <assert.h>
#include <string.h>


Service creeazaService()
{
	Service rez;
	rez.participanti = creeazaListaGoala(distrugeParticipant);
	rez.listaUndo = creeazaListaGoala(distrugeLista);
	return rez;
}



/*
	Functia adauga un participant in lista de participanti.
	input: l       - obiect de tip listaParticipanti
	       nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: 0 - participantul a fost adaugat
	        1 - altfel
*/
int adaugareParticipant(Service* l, char* nume, char* prenume, int scor)
{
	Participant* p = creeazaParticipant(nume, prenume, scor);
	listaParticipanti* toUndo = copiazaLista(l->participanti,copiazaParticipant);
	maresteCapacitateListaParticipanti(l->listaUndo);
	adaugaElement(l->listaUndo, toUndo);
	maresteCapacitateListaParticipanti(l->participanti);
	adaugaElement(l->participanti, p);
	return 0;
}

/*
	Functia actualizeaza un participant existent in lista de participanti.
	input: l       - obiect de tip listaParticipanti
		   nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: 0 - participantul a fost adaugat
			1 - altfel
*/
int actualizareParticipant(Service* l, char* nume, char* prenume, int scor)
{
	int gasit = 0;
	for (int i = 0; i < l->participanti->lungime; i++) 
		if (strcmp(nume, getNume(l->participanti->elemente[i])) == 0)
		{
			listaParticipanti* toUndo = copiazaLista(l->participanti,copiazaParticipant);
			maresteCapacitateListaParticipanti(l->listaUndo);
			adaugaElement(l->listaUndo, toUndo);
			setNume(l->participanti->elemente[i], nume);
			setPrenume(l->participanti->elemente[i], prenume);
			setScor(l->participanti->elemente[i], scor);
			gasit = 1;
		}
	if (gasit == 1)
		return 0;
	else
		return 1;
}

/*
	Functia sterge un participant existent in lista de participanti.
	input: l       - obiect de tip listaParticipanti
		   nume    - vector de caractere
	output: 0 - participantul a fost adaugat
			1 - altfel
*/
int stergereParticipant(Service* l, char* nume)
{
	int gasit = 0;
	for (int i = 0; i < l->participanti->lungime; i++)
		if (strcmp(nume, getNume(l->participanti->elemente[i])) == 0)
		{
			listaParticipanti* toUndo = copiazaLista(l->participanti, copiazaParticipant);
			maresteCapacitateListaParticipanti(l->listaUndo);
			adaugaElement(l->listaUndo, toUndo);
			gasit = 1;
			distrugeParticipant(l->participanti->elemente[i]);
			for (int j = i; j < l->participanti->lungime - 1; j++)
				l->participanti->elemente[j] = l->participanti->elemente[j + 1];
			l->participanti->lungime -= 1;
		}
	if (gasit == 1)
		return 0;
	else
		return 1;
}

/*
	Functia filtreaza o lista de participanti dupa scor, scorul participantilor trebuie sa fie
	mai mic decat cel transmis prin parametru.
	input: l    - obiect de tip listaParticipanti
	       scor - numar intreg
	output: lista - obiect de tip listaParticipanti
*/
listaParticipanti* filtrareParticipantiScor(Service* l, int scor)
{
	listaParticipanti* lista = creeazaListaGoala(distrugeParticipant);
	for (int i = 0; i < l->participanti->lungime; i++)
		if (getScor(l->participanti->elemente[i]) < scor) {
			Participant* p = creeazaParticipant(getNume(l->participanti->elemente[i]), getPrenume(l->participanti->elemente[i]), getScor(l->participanti->elemente[i]));
			adaugaElement(lista, p);
		}
			
	return lista;
}

/*
	Functia filtreaza o lista de participanti dupa o litera, numele participantilor trebuie 
	sa inceapa cu litera transmisa prin parametru.
	input: l      - obiect de tip listaParticipanti
		   litera - caracter
	output: lista - obiect de tip listaParticipanti
*/
listaParticipanti* filtrareParticipantiLitera(Service* l, char litera)
{
	listaParticipanti* lista = creeazaListaGoala(distrugeParticipant);
	for (int i = 0; i < l->participanti->lungime; i++)
		if (getNume(l->participanti->elemente[i])[0] == litera) {
			Participant* p = creeazaParticipant(getNume(l->participanti->elemente[i]), getPrenume(l->participanti->elemente[i]), getScor(l->participanti->elemente[i]));
			adaugaElement(lista, p);

		}
	return lista;
}



listaParticipanti* filtrareParticipantiLiteraPrenume(Service* l, char litera)
{
	listaParticipanti* lista = creeazaListaGoala(distrugeParticipant);
	for (int i = 0; i < l->participanti->lungime; i++)
		if (getPrenume(l->participanti->elemente[i])[0] == litera) {
			Participant* p = creeazaParticipant(getNume(l->participanti->elemente[i]), getPrenume(l->participanti->elemente[i]), getScor(l->participanti->elemente[i]));
			adaugaElement(lista, p);

		}
	return lista;
}


/*
	Functia compara 2 stringuri.
	input: el1 - obiect de tip Participant
		   el2 - obiect de tip Participant
	output: 1 - primul string se afla dupa cel de-al doilea in ordine lexicografica
	        0 - cele 2 stringuri sunt egale
		   -1 - primul string se afla inaintea celui de-al doilea in ordine lexicografica
*/
int comparaParticipantNume(Participant *el1, Participant *el2)
{
	return strcmp(getNume(el1), getNume(el2));
}

/*
	Functia compara 2 numere intregi.
	input: el1 - obiect de tip Participant
		   el2 - obiect de tip Participant
	output: 1 - primul numar este mai mare decat cel de-al doilea
	        0 - cele 2 numere sunt egale
		   -1 - primul numar este mai mic decat cel de-al doilea
*/
int comparaParticipantScor(Participant *el1, Participant *el2)
{
	if (getScor(el1) > getScor(el2))
		return 1;
	if (getScor(el1) == getScor(el2))
		return 0;
	//if (getScor(el1) < getScor(el2))
	return -1;
}

/*
	Functia sorteaza crescator/descrescator o lista de participanti dupa un criteriu returnat printr-o functie.
	input: l              - obiect de tip listaParticipanti
	       optiuneSortare - numar intreg 1 - sortare crescatoare
		                                -1 - sortare descrescatoare
		   cmp            - functie care returneaza  1  - primul element ii mai mare decat cel de-al doilea
		                                             0  - cele 2 elemente sunt egale
													-1 - primul element ii mai mic decat cel de-al doilea
	output: lista - obiect de tip listaParticipanti
*/
void sortareParticipanti(Service* l, int optiuneSortare, Cmp cmp)
{
	int ok = 0;
	TElem aux;
	do
	{
		ok = 1;
		for (int i = 0; i < l->participanti->lungime - 1; i++)
		{
			if (cmp(l->participanti->elemente[i], l->participanti->elemente[i + 1]) * optiuneSortare > 0)
			{
				aux = l->participanti->elemente[i];
				l->participanti->elemente[i] = l->participanti->elemente[i + 1];
				l->participanti->elemente[i + 1] = aux;
				ok = 0;
			}
		}
	} while (!ok);
}

void distrugeService(Service* l)
{
	distrugeLista(l->participanti);
	distrugeLista(l->listaUndo);
	
}

void testAdaugareParticipant()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	adaugareParticipant(&service, "Rafa", "Rafael", 85);
	assert(lungimeLista(service.participanti) == 2);

	distrugeService(&service);
}

void testActualizareParticipant()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	actualizareParticipant(&service, "Pop", "Alexandru", 60);
	actualizareParticipant(&service, "Alex", "Alexandru", 60);
	assert(strcmp(getPrenume(service.participanti->elemente[0]), "Alexandru") == 0);
	assert(getScor(service.participanti->elemente[0]) == 60);
	
	distrugeService(&service);
}

void testStergereParticipant()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	adaugareParticipant(&service, "Vasile", "Vasilescu", 100);
	stergereParticipant(&service, "Pop");
	stergereParticipant(&service, "Alex");
	assert(lungimeLista(service.participanti) == 1);

	distrugeService(&service);
}

void testFiltrareParticipantiScor()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	adaugareParticipant(&service, "Lonca", "Sorin", 15);
	adaugareParticipant(&service, "Popescu", "Alexandru", 30);
	adaugareParticipant(&service, "Marian", "Ruxandra", 60);
	listaParticipanti* listaFiltrata = filtrareParticipantiScor(&service, 50);
	assert(lungimeLista(listaFiltrata) == 2);
	assert(getScor(listaFiltrata->elemente[0]) == 15);
	assert(getScor(listaFiltrata->elemente[1]) == 30);

	distrugeLista(listaFiltrata);
	distrugeService(&service);
}

void testFiltrareParticipantiLitera()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	adaugareParticipant(&service, "Lonca", "Sorin", 15);
	adaugareParticipant(&service, "Popescu", "Alexandru", 30);
	adaugareParticipant(&service, "Marian", "Ruxandra", 60);
	listaParticipanti* listaFiltrata = filtrareParticipantiLitera(&service, 'P');
	assert(lungimeLista(listaFiltrata) == 2);
	assert(strcmp(getNume(listaFiltrata->elemente[0]), "Pop") == 0);
	assert(strcmp(getNume(listaFiltrata->elemente[1]), "Popescu") == 0);

	distrugeLista(listaFiltrata);
	distrugeService(&service);
}

void testFiltrareParticipantiLiteraPrenume()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	adaugareParticipant(&service, "Lonca", "Sorin", 15);
	adaugareParticipant(&service, "Popescu", "Maria", 30);
	adaugareParticipant(&service, "Marian", "Ruxandra", 60);
	listaParticipanti* listaFiltrata = filtrareParticipantiLiteraPrenume(&service, 'M');
	assert(lungimeLista(listaFiltrata) == 2);
	assert(strcmp(getPrenume(listaFiltrata->elemente[0]), "Mihai") == 0);
	assert(strcmp(getPrenume(listaFiltrata->elemente[1]), "Maria") == 0);

	distrugeLista(listaFiltrata);
	distrugeService(&service);
}

void testComparaParticipantNume()
{
	Participant* el1 = creeazaParticipant("Pop", "Mihai", 10);
	Participant* el2 = creeazaParticipant("Dan", "Alexandru", 10);
	Participant* el3 = creeazaParticipant("Pop", "Vasile", 10);
	assert(comparaParticipantNume(el1, el2) > 0);
	assert(comparaParticipantNume(el1, el3) == 0);
	assert(comparaParticipantNume(el2, el1) < 0);
	distrugeParticipant(el1);
	distrugeParticipant(el2);
	distrugeParticipant(el3);
}

void testComparaParticipantScor()
{
	Participant* el1 = creeazaParticipant("Pop", "Mihai", 10);
	Participant* el2 = creeazaParticipant("Dan", "Alexandru", 20);
	Participant* el3 = creeazaParticipant("Pop", "Vasile", 10);
	assert(comparaParticipantScor(el1, el2) < 0);
	assert(comparaParticipantScor(el1, el3) == 0);
	assert(comparaParticipantScor(el2, el1) > 0);
	distrugeParticipant(el1);
	distrugeParticipant(el2);
	distrugeParticipant(el3);
}

void testSortareParticipanti()
{
	Service service = creeazaService();
	adaugareParticipant(&service, "Pop", "Mihai", 100);
	adaugareParticipant(&service, "Lonca", "Sorin", 15);
	///nume
	sortareParticipanti(&service, 1, &comparaParticipantNume);
	assert(strcmp(getNume(service.participanti->elemente[0]), "Lonca") == 0);
	assert(strcmp(getNume(service.participanti->elemente[1]), "Pop") == 0);
	sortareParticipanti(&service, -1, &comparaParticipantNume);
	assert(strcmp(getNume(service.participanti->elemente[0]), "Pop") == 0);
	assert(strcmp(getNume(service.participanti->elemente[1]), "Lonca") == 0);
	///scor
	sortareParticipanti(&service, 1, &comparaParticipantScor);
	assert(getScor(service.participanti->elemente[0]) == 15);
	assert(getScor(service.participanti->elemente[1]) == 100);
	sortareParticipanti(&service, -1, &comparaParticipantScor);
	assert(getScor(service.participanti->elemente[0]) == 100);
	assert(getScor(service.participanti->elemente[1]) == 15);

	distrugeService(&service);
}
#pragma once
#include "listaParticipanti.h"

typedef int(*Cmp)(Participant *el1, Participant *el2);


typedef struct {
	listaParticipanti* participanti;
	listaParticipanti* listaUndo;
} Service;


Service creeazaService();

/*
	Functia adauga un participant in lista de participanti.
	input: l       - obiect de tip listaParticipanti
		   nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: 0 - participantul a fost adaugat
			1 - altfel
*/
int adaugareParticipant(Service* l, char* nume, char* prenume, int scor);


/*
	Functia actualizeaza un participant existent in lista de participanti.
	input: l       - obiect de tip listaParticipanti
		   nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: 0 - participantul a fost adaugat
			1 - altfel
*/
int actualizareParticipant(Service* l, char* nume, char* prenume, int scor);

/*
	Functia sterge un participant existent in lista de participanti.
	input: l       - obiect de tip listaParticipanti
		   nume    - vector de caractere
	output: 0 - participantul a fost adaugat
			1 - altfel
*/
int stergereParticipant(Service* l, char* nume);

/*
	Functia filtreaza o lista de participanti dupa scor, scorul participantilor trebuie sa fie
	mai mic decat cel transmis prin parametru.
	input: l    - obiect de tip listaParticipanti
		   scor - numar intreg
	output: lista - obiect de tip listaParticipanti
*/
listaParticipanti* filtrareParticipantiScor(Service* l, int scor);

/*
	Functia filtreaza o lista de participanti dupa o litera, numele participantilor trebuie
	sa inceapa cu litera transmisa prin parametru.
	input: l      - obiect de tip listaParticipanti
		   litera - caracter
	output: lista - obiect de tip listaParticipanti
*/
listaParticipanti* filtrareParticipantiLitera(Service* l, char litera);


listaParticipanti* filtrareParticipantiLiteraPrenume(Service* l, char litera);

/*
	Functia compara 2 stringuri.
	input: el1 - obiect de tip Participant
		   el2 - obiect de tip Participant
	output: 1 - primul string se afla dupa cel de-al doilea in ordine lexicografica
			0 - cele 2 stringuri sunt egale
		   -1 - primul string se afla inaintea celui de-al doilea in ordine lexicografica
*/
int comparaParticipantNume(Participant *el1, Participant *el2);

/*
	Functia compara 2 numere intregi.
	input: el1 - obiect de tip Participant
		   el2 - obiect de tip Participant
	output: 1 - primul numar este mai mare decat cel de-al doilea
			0 - cele 2 numere sunt egale
		   -1 - primul numar este mai mic decat cel de-al doilea
*/
int comparaParticipantScor(Participant *el1, Participant *el2);

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
void sortareParticipanti(Service* l, int optiuneSortare, Cmp cmp);


void distrugeService(Service* l);

void testAdaugareParticipant();
void testActualizareParticipant();
void testStergereParticipant();
void testFiltrareParticipantiScor();
void testFiltrareParticipantiLitera();
void testFiltrareParticipantiLiteraPrenume();
void testComparaParticipantNume();
void testComparaParticipantScor();
void testSortareParticipanti();

#pragma once
#include "participant.h"
#include "listaParticipanti.h"
#include "serviceParticipant.h"
#include "validareDate.h"

/*
	Functia afiseaza meniul programului.
	input: -
	output: -
*/
void uiMeniu();

/*
	Functia citeste parametrii necesari unui obiect de tip Participant.
	input: nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: -
*/
void uiCitesteParticipant(char* nume, char* prenume, char* scor);

/*
	Functia afiseara elementele de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: -
*/
void uiAfisareListaParticipanti(listaParticipanti* l);

/*
	Functia adauga un obiect de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: mesaj
*/
void uiAdaugareParticipant(Service* l);

/*
	Functia actualizeaza un obiect existent de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: mesaj
*/
void uiActualizareParticipant(Service* l);

/*
	Functia sterge un obiect existent de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: mesaj
*/
void uiStergereParticipant(Service* l);

/*
	Functia filtreaza o lista de participanti in functie de un anumit criteriu.
	input: l - obiect de tip listaParticipanti
	output: lista filtrata
*/
void uiFiltrareParticipanti(Service* l);

/*
	Functia sorteaza o lista de participanti in functie de un anumit criteriu.
	input: l - obiect de tip listaParticipanti
	output: lista filtrata
*/
void uiSortareParticipanti(Service* l);

void testAll();
void run();
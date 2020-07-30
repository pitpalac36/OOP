#pragma once

typedef struct
{
	char *nume;
	char *prenume;
	int scor;
}Participant;

Participant* copiazaParticipant(Participant* p);

/*
	Functia returneaza parametrul nume al unui obiect de tip Participant.
	input: p - obiect de tip Participant
	output: nume - vector de caractere
*/
char* getNume(Participant* p);

/*
	Functia returneaza parametrul prenume al unui obiect de tip Participant.
	input: p - obiect de tip Participant
	output: prenume - vector de caractere
*/
char* getPrenume(Participant* p);

/*
	Functia returneaza parametrul scor al unui obiect de tip Participant.
	input: p - obiect de tip Participant
	output: scor - numar intreg
*/
int getScor(Participant* p);

/*
	Functia creeaza un obiect de tip Participant.
	input: nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: participant - obiect de tip Participant
*/
Participant* creeazaParticipant(char* nume, char* prenume, int scor);

/*
	Functia seteaza parametrul nume al unui obiect de tip Participant.
	input: p    - obiect de tip Participant
		   nume - vector de caractere
	output: -
*/
void setNume(Participant* p, char* nume);

/*
	Functia seteaza parametrul prenume al unui obiect de tip Participant.
	input: p       - obiect de tip Participant
		   prenume - vector de caractere
	output: -
*/
void setPrenume(Participant* p, char* prenume);

/*
	Functia seteaza parametrul scor al unui obiect de tip Participant.
	input: p    - obiect de tip Participant
		   scor - numar intreg
	output: -
*/
void setScor(Participant* p, int scor);

/*
	Functia distruge un obiect de tip Participant.
	input: p - obiect de tip Participant
	output: -
*/
void distrugeParticipant(Participant *p);

void testCreeazaParticipant();
void testDistrugeParticipant();
void testGetNume();
void testGetPrenume();
void testGetScor();
void testSetNume();
void testSetPrenume();
void testSetScor();
void testCopiaza();
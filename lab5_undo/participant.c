#include "participant.h"

#include <string.h>
#include <stdlib.h>
#include <assert.h>

/*
	Functia creeaza un obiect de tip Participant.
	input: nume    - vector de caractere
	       prenume - vector de caractere
		   scor    - numar intreg
	output: participant - obiect de tip Participant
*/
Participant* creeazaParticipant(char* nume, char* prenume, int scor)
{
	Participant* participant = malloc(sizeof(Participant));
	participant->nume = malloc(sizeof(char) * strlen(nume) + 1);
	participant->prenume = malloc(sizeof(char) * strlen(prenume) + 1);
	strcpy(participant->nume, nume);
	strcpy(participant->prenume, prenume);
	participant->scor = scor;
	return participant;
}


Participant* copiazaParticipant(Participant* p) {
	return creeazaParticipant(p->nume, p->prenume, p->scor);
}


/*
	Functia returneaza parametrul nume al unui obiect de tip Participant.
	input: p - obiect de tip Participant
	output: nume - vector de caractere
*/
char* getNume(Participant* p)
{
	return p->nume;
}

/*
	Functia returneaza parametrul prenume al unui obiect de tip Participant.
	input: p - obiect de tip Participant
	output: prenume - vector de caractere
*/
char* getPrenume(Participant* p)
{
	return p->prenume;
}

/*
	Functia returneaza parametrul scor al unui obiect de tip Participant.
	input: p - obiect de tip Participant
	output: scor - numar intreg
*/
int getScor(Participant* p)
{
	return p->scor;
}

/*
	Functia seteaza parametrul nume al unui obiect de tip Participant.
	input: p    - obiect de tip Participant
	       nume - vector de caractere
	output: -
*/
void setNume(Participant* p, char* nume)
{
	free(p->nume);
	p->nume = malloc(sizeof(char) * strlen(nume) + 1);
	strcpy(p->nume, nume);
}

/*
	Functia seteaza parametrul prenume al unui obiect de tip Participant.
	input: p       - obiect de tip Participant
		   prenume - vector de caractere
    output: -
*/
void setPrenume(Participant* p, char* prenume)
{
	free(p->prenume);
	p->prenume = malloc(sizeof(char) * strlen(prenume) + 1);
	strcpy(p->prenume, prenume);
}

/*
	Functia seteaza parametrul scor al unui obiect de tip Participant.
	input: p    - obiect de tip Participant
		   scor - numar intreg
	output: -
*/
void setScor(Participant* p, int scor)
{
	p->scor = scor;
}

/*
	Functia distruge un obiect de tip Participant.
	input: p - obiect de tip Participant
	output: -
*/
void distrugeParticipant(Participant *p)
{
	free(p->nume);
	free(p->prenume);
	free(p);
}

void testCreeazaParticipant()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	assert(strcmp(getNume(p), "Pop") == 0);
	assert(strcmp(getPrenume(p), "Mihai") == 0);
	assert(p->scor == 100);

	distrugeParticipant(p);
}

void testGetNume()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	assert(strcmp(getNume(p), "Pop") == 0);

	distrugeParticipant(p);
}

void testGetPrenume()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	assert(strcmp(getPrenume(p), "Mihai") == 0);

	distrugeParticipant(p);
}

void testGetScor()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	assert(getScor(p) == 100);

	distrugeParticipant(p);
}

void testSetNume()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	setNume(p, "Vasile");
	assert(strcmp(getNume(p), "Vasile") == 0);

	distrugeParticipant(p);
}

void testSetPrenume()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	setPrenume(p, "Alexandru");
	assert(strcmp(getPrenume(p), "Alexandru") == 0);

	distrugeParticipant(p);
}

void testSetScor()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	setScor(p, 10);
	assert(getScor(p) == 10);

	distrugeParticipant(p);
}

void testCopiaza()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	Participant* copie = copiazaParticipant(p);
	assert(strcmp(getNume(copie), "Pop") == 0);
	assert(strcmp(getPrenume(copie), "Mihai") == 0);
	assert(getScor(copie) == 100);
	distrugeParticipant(p);
	distrugeParticipant(copie);
}

void testDistrugeParticipant()
{
	Participant* p = creeazaParticipant("Pop", "Mihai", 100);
	distrugeParticipant(p);
}
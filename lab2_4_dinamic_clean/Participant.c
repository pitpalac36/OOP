#include "Participant.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

Participant creeazaParticipant(char* nume, char* prenume, int scor)
{
	Participant p;
	size_t sizeNume = strlen(nume) + 1;
	p.nume = malloc(sizeof(char) * sizeNume);
	strcpy_s(p.nume, sizeNume, nume);
	size_t sizePrenume = strlen(prenume) + 1;
	p.prenume = malloc(sizeof(char) * sizePrenume);
	strcpy_s(p.prenume, sizePrenume, prenume);
	p.scor = scor;
	return p;
}

void distrugeParticipant(Participant* p)
{
	free(p->nume);
	free(p->prenume);
	p->nume = NULL;
	p->prenume = NULL;
	p->scor = -1;
}

void setScor(Participant* p, int scor)
{
	p->scor = scor;
}


int valideaza(Participant p)
{
	char* rez = strtok(p.nume, " ");
	if (rez == NULL)
		return 1;
	rez = strtok(p.prenume, " ");
	if (rez == NULL)
		return 2;
	if (p.scor < 0)
		return 3;
	return 0;
}


void testCreeazaDistruge()
{
	Participant p1 = creeazaParticipant("popan", "ana", 50);
	Participant p2 = creeazaParticipant("sava", "andrei", 100);
	assert(strcmp(p1.nume, "popan") == 0);
	assert(strcmp(p1.prenume, "ana") == 0);
	distrugeParticipant(&p1);
	distrugeParticipant(&p2);
	assert(p1.nume == '\0');
	assert(p2.prenume == '\0');
	assert(p1.scor == p2.scor);
}


void testValideaza() {
	Participant p1 = creeazaParticipant("", "ana", 50);
	Participant p2 = creeazaParticipant("sava", "", 100);
	Participant p3 = creeazaParticipant("popan", "ana", -13);
	Participant p4 = creeazaParticipant("ionel", "ionut", 123);
	assert(valideaza(p1) == 1);
	assert(valideaza(p2) == 2);
	assert(valideaza(p3) == 3);
	assert(valideaza(p4) == 0);
	distrugeParticipant(&p1);
	distrugeParticipant(&p2);
	distrugeParticipant(&p3);
	distrugeParticipant(&p4);
}
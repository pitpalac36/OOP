#include "participant.h"
#include <string.h>
#include <assert.h>

Participant creeazaParticipant(char* nume, char* prenume, int scor)
{
	Participant p;
	strcpy_s(p.nume, sizeof(p.nume), nume);
	strcpy_s(p.prenume, sizeof(p.prenume), prenume);
	p.scor = scor;
	return p;
}


void distrugeParticipant(Participant* p)
{
	p->nume[0] = '\0';
	p->prenume[0] = '\0';
	p->scor = -1;
}

void setScor(Participant* p, int scorNou)
{
	p->scor = 0;
	p->scor = scorNou;
}

int valideaza(Participant p) {
	if (strcmp(p.nume,"") == 0)
		return 1;
	if (strcmp(p.prenume, "") == 0)
		return 2;
	if (p.scor < 0)
		return 3;
	return 0;
}


void testCreeazaDistruge() {
	Participant p = creeazaParticipant("pop", "mihai", 40);
	assert(strcmp(p.nume,"pop") == 0);
	assert(strcmp(p.prenume, "mihai") == 0);
	assert(p.scor == 40);
	distrugeParticipant(&p);
	assert(strlen(p.nume) == 0);
	assert(strlen(p.prenume) == 0);
	assert(p.scor == -1);
}

void testActualizeaza() {
	char nume[30] = "pop";
	char prenume[30] = "mihai";
	Participant p = creeazaParticipant("pop", "mihai", 40);
	setScor(&p, 100);
	assert(p.scor == 100);
	char nume1[30];
	char prenume1[30];
	strcpy_s(nume1, sizeof(p.nume),p.nume);
	strcpy_s(prenume1, sizeof(p.prenume),p.prenume);
	assert(strcmp(prenume1, "mihai") == 0);
	assert(strcmp(nume1, "pop") == 0);
}

void testValideaza() {
	Participant p1 = creeazaParticipant("", "mihai", 40);
	Participant p2 = creeazaParticipant("pop", "", 40);
	Participant p3 = creeazaParticipant("pop", "mihai", -13);
	Participant p4 = creeazaParticipant("pop", "mihai", 13);
	assert(valideaza(p1) == 1);
	assert(valideaza(p2) == 2);
	assert(valideaza(p3) == 3);
	assert(valideaza(p4) == 0);
	distrugeParticipant(&p1);
	distrugeParticipant(&p2);
	distrugeParticipant(&p3);
	distrugeParticipant(&p4);
}
#pragma once
#include <stdbool.h>

typedef struct {
	char nume[30];
	char prenume[30];
	int scor;
}Participant;


/*
 creeaza un nou participant
*/
Participant creeazaParticipant( char* nume, char* prenume, int scor );


/*
 sterge un participant -> dealocarea memoriei ocupata de acesta
*/
void distrugeParticipant(Participant* p);


/*
 setter pt scor
*/
void setScor(Participant* p, int scor);

/*
 validarea unui Participant
*/
int valideaza(Participant);



void testCreeazaDistruge();


void testActualizeaza();
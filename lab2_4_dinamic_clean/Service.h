#pragma once
#include "Repo.h"


DynamicArray createList();


void destroyList(DynamicArray* c);


int addParticipant(DynamicArray* c, char* nume, char* prenume, int scor);


void removeAll(DynamicArray* c);


int updateOne(DynamicArray* c, char* nume, char* prenume, int scorNou);


DynamicArray filtreaza(DynamicArray c, char* substr);

void testAdaugareStergereActualizareFiltrare();
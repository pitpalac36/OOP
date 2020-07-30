#pragma once
#include "Repo.h"


int adaugaService(List* lista, char* nume, char* prenume, int scor);


int actualizeazaService(List* lista, char* nume, char* prenume, int scorNou);


void stergeToti(List* lista);


List filtreaza(List lista, char* substr);


void testAdaugareStergereActualizareFiltrare();
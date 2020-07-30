#pragma once
#include <string.h>
#include <stdbool.h>
#include "Repo.h"


/*
 returneaza un bool ce indica daca cele doua elemente sunt in relatie sau nu;
 pt ordine crescatoare:
 - daca atributul dat este "nume", cele 2 elemente sunt in relatie <=> primul este inaintea
		celuilalt dpdv lexicografic
 - altfel (atributul dat este "scor"), cele 2 elemente sunt in relatie <=> scorul primului este
		mai mic decat scorul celui de-al doilea
 (pt ordine descrescatoare e exact invers)
*/
bool inRelatie(ElemType e1, ElemType e2, char* atribut, char* ordine);


#include "validareDate.h"

#include <string.h>
#include <assert.h>
#include <ctype.h>

/*
	Functia verifica daca un sir de caractere contine altceva inafara de litere.
	input: string - sir de caractere
	output: 1 - sirul contine doar litere
			0 - altfel
*/
int validareString(char *string)
{
	int lungime = strlen(string);
	for (int i = 0; i < lungime; i++)
		if (!isalpha(string[i]))
			return 0;
	return 1;
}

/*
	Functia verifica daca un sir de caractere contine altceva inafara de numere.
	input: string - sir de caractere
	output: numar - numarul construit din sirul de caractere
			-1    - altfel
*/
int validareIntreg(char *string)
{
	int numar = 0;
	int lungime = strlen(string);
	for (int i = 0; i < lungime; i++)
		if (!isdigit(string[i]))
			return -1;
	for (int i = 0; i < lungime; i++)
		numar = numar * 10 + string[i] - 48;
	return numar;
}

void testValidareString()
{
	char textCorect[] = "Pop";
	char textGresit[] = "Pop1";
	assert(validareString(textCorect) == 1);
	assert(validareString(textGresit) == 0);
}

void testValidareIntreg()
{
	char textCorect[] = "1234";
	char textGresit[] = "12a4";
	assert(validareIntreg(textCorect) == 1234);
	assert(validareIntreg(textGresit) == -1);
}
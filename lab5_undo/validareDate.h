#pragma once

/*
	Functia verifica daca un sir de caractere contine altceva inafara de litere.
	input: string - sir de caractere
	output: 1 - sirul contine doar litere
			0 - altfel
*/
int validareString(char *string);

/*
	Functia verifica daca un sir de caractere contine altceva inafara de numere.
	input: string - sir de caractere
	output: numar - numarul construit din sirul de caractere
			0     - altfel
*/
int validareIntreg(char *string);

void testValidareString();
void testValidareIntreg();
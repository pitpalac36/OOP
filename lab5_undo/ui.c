#include "ui.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*
	Functia afiseaza meniul programului.
	input: -
	output: -
*/
void uiMeniu()
{
	printf("0. Exit\n");
	printf("1. Afisare lista participanti\n");
	printf("2. Adaugare participant\n");
	printf("3. Actualizare participant existent\n");
	printf("4. Stergere participant\n");
	printf("5. Filtrare participanti\n");
	printf("6. Sortare participanti\n");
	printf("7. Undo\n");
	printf(">");

}

/*
	Functia citeste parametrii necesari unui obiect de tip Participant.
	input: nume    - vector de caractere
		   prenume - vector de caractere
		   scor    - numar intreg
	output: -
*/
void uiCitesteParticipant(char* nume, char* prenume, char* scor)
{
	printf("Dati numele participantului: ");
	scanf("%s", nume);
	printf("Dati prenumele participantului: ");
	scanf("%s", prenume);
	printf("Dati scorul participantului: ");
	scanf("%s", scor);
}

/*
	Functia afiseara elementele de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: -
*/
void uiAfisareListaParticipanti(listaParticipanti* l)
{
	if (l->lungime == 0)
		printf("Lista de participanti este goala!\n");
	else
		for (int i = 0; i < l->lungime; i++) {

			printf("%d.\nNume: %s\nPrenume: %s\nScor: %d\n", i, getNume(l->elemente[i]), getPrenume(l->elemente[i]), getScor(l->elemente[i]));
		}
			
	printf("\n");
}

/*
	Functia adauga un obiect de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: mesaj
*/
void uiAdaugareParticipant(Service* l)
{
	char* nume = malloc(sizeof(char) * 30);
	char* prenume = malloc(sizeof(char) * 30);
	char* scorC = malloc(sizeof(char) * 30);
	int scorI, succes;
	uiCitesteParticipant(nume, prenume, scorC);
	scorI = validareIntreg(scorC);
	if (validareString(nume) && validareString(prenume) && scorI != -1)
	{
		succes = adaugareParticipant(l, nume, prenume, scorI);
		if (succes == 0)
			printf("Participantul a fost adaugat cu succes!\n");
		else
			printf("Participantul nu a fost adaugat!\n");
		printf("\n");
	}
	else
	{
		printf("Datele participantului sunt gresite!\n\n");
	}
	free(nume);
	free(prenume);
	free(scorC);
}

/*
	Functia actualizeaza un obiect existent de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: mesaj
*/
void uiActualizareParticipant(Service* l)
{
	char* nume, *prenume, *scorC;
	nume = malloc(sizeof(char) * 30);
	prenume = malloc(sizeof(char) * 30);
	scorC = malloc(sizeof(char) * 30);
	int scorI, succes;
	uiCitesteParticipant(nume, prenume, scorC);
	scorI = validareIntreg(scorC);
	if (validareString(nume) && validareString(prenume) && scorI != -1)
	{
		succes = actualizareParticipant(l, nume, prenume, scorI);
		if (succes == 0)
			printf("Participantul a fost actualizat cu succes!\n");
		else
			printf("Participantul nu a fost actualizat!\n");
		printf("\n");
	}
	else
	{
		printf("Datele participantului sunt gresite!\n\n");
	}
	free(nume);
	free(prenume);
	free(scorC);
}

/*
	Functia sterge un obiect existent de tip Participant din lista de participanti.
	input: l - obiect de tip listaParticipanti
	output: mesaj
*/
void uiStergereParticipant(Service* l)
{
	char* nume;
	nume = malloc(sizeof(char) * 30);
	int succes;
	printf("Dati numele participantului: ");
	scanf("%s", nume);
	if (validareString(nume))
	{
		succes = stergereParticipant(l, nume);
		if (succes == 0)
			printf("Participantul a fost sters cu succes!\n");
		else
			printf("Participantul nu a fost sters!\n");
		printf("\n");
	}
	else
	{
		printf("Datele participantului sunt gresite!\n\n");
	}
	free(nume);
}

/*
	Functia filtreaza o lista de participanti in functie de un anumit criteriu.
	input: l - obiect de tip listaParticipanti
	output: lista filtrata
*/
void uiFiltrareParticipanti(Service* l)
{
	char *optiuneC, *scorC;
	optiuneC = malloc(sizeof(char) * 30);
	scorC = malloc(sizeof(char) * 30);
	char litera;
	printf("Criterii de filtrare\n");
	printf("1. Cei ai caror nume incep cu o litera data\n");
	printf("2. Cei ai caror prenume incep cu o litera data\n");
	printf("3. Cei care au un scor mai mic decat o valoare data\n");
	scanf("%s",	optiuneC);
	int optiune = validareIntreg(optiuneC);
	if (optiune != -1)
	{
		if (optiune == 1)
		{
			printf("Dati o litera: \n");
			scanf(" %c", &litera);
			listaParticipanti* listaFiltrata = filtrareParticipantiLitera(l, litera);
			uiAfisareListaParticipanti(listaFiltrata);
			distrugeLista(listaFiltrata);
		}
		else
		{
			if (optiune == 2)
			{
				printf("Dati o litera: \n");
				scanf(" %c", &litera);
				listaParticipanti* listaFiltrata = filtrareParticipantiLiteraPrenume(l, litera);
				uiAfisareListaParticipanti(listaFiltrata);
				distrugeLista(listaFiltrata);

			}
			else {
				if (optiune == 3)
				{
					printf("Dati un scor: \n");
					scanf("%s", scorC);
					int scor = validareIntreg(scorC);
					if (scor != -1)
					{
						listaParticipanti* listaFiltrata = filtrareParticipantiScor(l, scor);
						uiAfisareListaParticipanti(listaFiltrata);
						distrugeLista(listaFiltrata);
					}
					else
					{
						printf("Datele au fost introduse gresit!\n\n");
					}

				}
				else
				{
					printf("Datele au fost introduse gresit!\n\n");
				}
			}
		}
	}
	else
	{
		printf("Datele au fost introduse gresit!\n\n");
	}
	free(optiuneC);
	free(scorC);
	
}

/*
	Functia sorteaza o lista de participanti in functie de un anumit criteriu.
	input: l - obiect de tip listaParticipanti
	output: lista filtrata
*/
void uiSortareParticipanti(Service* l)
{

	char *optiuneCriteriuC, *optiuneSortareC;
	optiuneCriteriuC = malloc(sizeof(char) * 30);
	optiuneSortareC = malloc(sizeof(char) * 30);
	printf("Tip de sortare:\n");
	printf("1. Crescator\n");
	printf("2. Descrescator\n");
	scanf("%s", optiuneSortareC);
	int optiuneSortare = validareIntreg(optiuneSortareC);
	if ((optiuneSortare == 1 || optiuneSortare == 2) && optiuneSortare != -1)
	{
		printf("Criterii de sortare\n");
		printf("1. Dupa nume\n");
		printf("2. Dupa scor\n");
		scanf("%s", optiuneCriteriuC);
		int optiuneCriteriu = validareIntreg(optiuneCriteriuC);
		if ((optiuneCriteriu == 1 || optiuneCriteriu == 2) && optiuneCriteriu != -1)
		{
			if (optiuneCriteriu == 1)
				if (optiuneSortare == 1)
					sortareParticipanti(l, 1, &comparaParticipantNume);
				else
					sortareParticipanti(l, -1, &comparaParticipantNume);
			if (optiuneCriteriu == 2)
				if (optiuneSortare == 1)
					sortareParticipanti(l, 1, &comparaParticipantScor);
				else
					sortareParticipanti(l, -1, &comparaParticipantScor);
			uiAfisareListaParticipanti(l->participanti);
		}
		else
		{
			printf("Datele au fost introduse gresit!\n\n");
		}
	}	
	else
	{
		printf("Datele au fost introduse gresit!\n\n");
	}
	free(optiuneCriteriuC);
	free(optiuneSortareC);
}


int undo(Service* service) {
	if (lungimeLista(service->listaUndo) == 0) {
		return 1;
	}
	listaParticipanti* l = stergeUltim(service->listaUndo);
	distrugeLista(service->participanti);
	service->participanti = l;
	return 0;
}



void testAll()
{
	///validareUi
	testValidareString();
	testValidareIntreg();
	///participant
	testCreeazaParticipant();
	testDistrugeParticipant();
	testGetNume();
	testGetPrenume();
	testGetScor();
	testSetNume();
	testSetPrenume();
	testSetScor();
	testCopiaza();
	///listaParticipanti
	testCreeazaListaGoala();
	testAdaugaElement();
	testGetElement();
	testLungimeLista();
	testDistrugeLista();
	testCopiazaLista();
	testMaresteCapacitateListaParticipanti();
	testStergeUltim();
	///serviceParticipant
	testAdaugareParticipant();
	testActualizareParticipant();
	testStergereParticipant();
	testFiltrareParticipantiScor();
	testFiltrareParticipantiLitera();
	testFiltrareParticipantiLiteraPrenume();
	testComparaParticipantNume();
	testComparaParticipantScor();
	testSortareParticipanti();
}

void run()
{
	Service service = creeazaService();
	int ruleaza = 1;
	while (ruleaza)
	{
		uiMeniu();
		char* cmdC;
		cmdC = malloc(sizeof(char) * 30);
		scanf("%s", cmdC);
		int cmdI = validareIntreg(cmdC);
		if (cmdI != -1)
		{
			switch (cmdI)
			{
			case 0:
				ruleaza = 0;
				break;
			case 1:
				uiAfisareListaParticipanti((service.participanti));
				break;
			case 2:
				uiAdaugareParticipant(&service);
				break;
			case 3:
				uiActualizareParticipant(&service);
				break;
			case 4:
				uiStergereParticipant(&service);
				break;
			case 5:
				uiFiltrareParticipanti(&service);
				break;
			case 6:
				uiSortareParticipanti(&service);
				break;
			case 7:
				if (undo(&service) != 0) {
					printf("Nu se mai poate efectua UNDO!\n");
				}
				break;
			default:
				printf("Comanda invalida!\n");
			}
		}
		else
		{
			printf("Datele introduse sunt gresite!\n\n");
		}
		free(cmdC);
	}
	distrugeService(&service);
}
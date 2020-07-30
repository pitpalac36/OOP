#include "Participant.h"
#include "Repo.h"
#include "Service.h"
#include <stdio.h>
#include <stdlib.h>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "sortare.h"
#include "bubbleSort.h"
#include "string.h"



void testAll() {
    testCreeazaDistruge();
    testValideaza();
    testCreateDestroy();
    testInsertDelete();
    testAdaugareStergereActualizareFiltrare();
    testRelatie();
    testSortare();
}


void citesteParticipant(DynamicArray* lista) {
    char nume[30];
    char prenume[30];
    int scor;
    printf("Nume : ");
    scanf_s("%s", nume, sizeof(nume));
    printf("Prenume : ");
    scanf_s("%s", prenume, sizeof(prenume));
    printf("Scor : ");
    scanf_s("%d", &scor);
    int eroare = addParticipant(lista, nume, prenume, scor);
    if (eroare == 1)
        printf("Nume invalid!");
    else
        if (eroare == 2)
            printf("Prenume invalid!");
        else
            if (eroare == 3)
                printf("Scor invalid!");
            else printf("Adaugat cu succes!\n");
}



void afiseazaToti(DynamicArray lista) {
    if (get(&lista, 0).scor == -1 || dimensiune(lista) == 0 || dimensiune(lista) < 0) {
        printf("Nu exista participanti!\n\n");
        return;
    }
    printf("Participanti:\n");
    for (int i = 0; i < dimensiune(lista); i++) {
        Participant p = get(&lista, i);
        printf("Nume:%s Prenume:%s Scor actual:%d\n", p.nume, p.prenume, p.scor);
    }
}


void sorteazaParticipanti(DynamicArray* lista) {
    char criteriu[30] = "";
    printf("Sortare dupa nume/scor :");
    scanf_s("%s", criteriu, sizeof(criteriu));
    if (strcmp(criteriu, "scor") != 0 && strcmp(criteriu, "nume") != 0)
        printf("Criteriu invalid!\n");
    else {
        char ordine[30] = "";
        printf("Sortare crescatoare/descrescatoare :");
        scanf_s("%s", ordine, sizeof(ordine));
        if (strcmp(ordine, "crescatoare") != 0 && strcmp(ordine, "descrescatoare") != 0)
            printf("Ordine invalida!\n");
        else {
            BubbleSort(lista, criteriu, ordine);
            afiseazaToti(*lista);
        }
    }
}


void actualizeazaParticipant(DynamicArray* lista) {
    char nume[30];
    char prenume[30];
    int scorNou;
    printf("Nume : ");
    scanf_s("%s", nume, sizeof(nume));
    printf("Prenume : ");
    scanf_s("%s", prenume, sizeof(prenume));
    printf("Scor nou : ");
    scanf_s("%d", &scorNou);
    int eroare = updateOne(lista, nume, prenume, scorNou);
    if (eroare == 1)
        printf("Scor invalid!\n");
    else
        if (eroare == 2)
            printf("Nu exista niciun participant %s %s\n", nume, prenume);
        else
            printf("A fost actualizat cu succes!\n");
}


void filtreazaParticipanti(DynamicArray lista) {
    printf("Filtrare dupa nume incepand cu :");
    char filterStr[30];
    scanf_s("%s", filterStr, sizeof(filterStr));
    DynamicArray filteredL = filtreaza(lista, filterStr);
    afiseazaToti(filteredL);
}


void run() {
    DynamicArray participanti = createList();
    int ruleaza = 1;
    while (ruleaza) {
        printf("1 Adaugare\n2 Actualizare\n3 Stergerea tuturor\n4 Filtrare\n5 Sortare\n6 Afisarea tuturor\n0 Exit\nComanda : ");
        int cmd = 0;
        scanf_s("%d", &cmd);
        switch (cmd) {
        case 1:
            citesteParticipant(&participanti);
            break;
        case 2:
            actualizeazaParticipant(&participanti);
            break;
        case 3:
            removeAll(&participanti);
            break;
        case 4:
            filtreazaParticipanti(participanti);
            break;
        case 5:
            sorteazaParticipanti(&participanti);
            break;
        case 6:
            afiseazaToti(participanti);
            break;
        case 0:
            ruleaza = 0;
            destroyList(&participanti);
            break;
        default:
            printf("Comanda invalida!!!\n");
            break;
        }
    }
}


int main() {
    testAll();
    run();
    _CrtDumpMemoryLeaks(); //print memory leak
    return 0; 
}
#pragma once
#include "Service.h"


class UI
{
private:
	Service& service;

	/*
		- citeste de la tastatura datele cartii de adaugat
		- apeleaza metoda addCarte din service
		- arunca ValidationException daca datele introduse de utilizator sunt invalide
		- arunca RepoException daca exista deja cartea
	*/
	void adaugaCarte();


	/*
		afiseaza toate cartile stocate in memorie
	*/
	void tipareste(const List<Carte>& carti);


	/*
		- citeste de la tastatura datele cartii de sters
		- apeleaza metoda stergeCarte din service
		- arunca ValidationException daca datele introduse de utilizator sunt invalide
		- arunca RepoException daca nu exista cartea
	*/
	void stergeCarte();


	/*
		- citeste de la tastatura datele cartii de modificat
		- apeleaza metoda schimbaCarte din service
		- arunca ValidationException daca datele introduse de utilizator sunt invalide
		- arunca RepoException daca nu exista nicio carte cu titlul si autorul respective
	*/
	void schimbaCarte();


	/*
		- citeste de la tastatura limita lexicografica superioara dupa care se doreste filtrarea in functie de titlu
		- apeleaza metoda filtreazaTitlu din service
	*/
	void filtrareTitlu();


	/*
		- citeste de la tastatura limita superioara dupa care se doreste filtrarea in functie de anAparitie
		- apeleaza metoda filtreazaTitlu din service
	*/
	void filtrareAn();


	void rapoarte();


public:
	UI(Service& s) : service{ s } {}


	// nu se permite copierea unui obiect de tip UI
	UI(const UI& other) = delete;


	// afiseaza optiunile posibile; preia comenzile utilizatorului si apeleaza metodele respective din UI
	void start();
};


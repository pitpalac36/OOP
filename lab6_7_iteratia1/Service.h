#pragma once
#include "Carte.h"
#include "Validator.h"
#include "Repository.h"
#include <functional>
using std::function;


class Service
{
private:
	CarteValidator& v;
	Repository& r;


	/*
	Functie generala de filtrare
	fct - poate fi o functie
	fct - poate fi lambda, am folosit function<> pentru a permite si functii lambda care au ceva in capture list
	returneaza doar cartile care trec de filtru (fct(carte)==true)
	*/
	vector<Carte> filtreaza(function<bool(const Carte&)> fct);

public:

	Service(Repository& repo, CarteValidator& val) : r{repo}, v{val}{}

	// nu se permite copierea unui obiect de tip Service
	Service(const Service& service) = delete;


	// returneaza vectorul de carti din Repository
	const vector<Carte>& getAll() noexcept {
		return r.getAll();
	}


	/*
		- adauga in Repository un obiect de tip Carte ale carui campuri sunt parametri primiti respectiv
		- arunca ValidationException daca parametri sunt invalizi
	*/
	void addCarte(const string& titlu, const string& autor, const string& gen, int an);


	/*
		- sterge din Repository un obiect de tip Carte ale carui campuri sunt parametri primiti respectiv
		- arunca ValidationException daca parametri sunt invalizi
	*/
	void stergeCarte(const string& titlu, const string& autor, const string& gen, int an);


	/*
		- modifica in Repository un obiect de tip Carte care are valorile titlului si autorului egale cu paarmetri titlu respectiv autor 
		- arunca ValidationException daca parametri sunt invalizi
	*/
	void schimbaCarte(const string& titlu, const string& autor, string& gen, int an);


	/*
		returneaza un vector cu obiectele de tip Carte din Repository care au titlul < valoarea parametrului titlu
	*/
	vector<Carte> filtreazaTitlu(string titlu);


	/*
		returneaza un vector cu obiectele de tip Carte din Repository care au anul < valoarea parametrului an
	*/
	vector<Carte> filtreazaAn(int an);


	/*
		returneaza un vector cu obiectele de tip Carte din Repository sortate crescator in functie de titlu
	*/
	vector<Carte> sorteazaTitlu();


	/*
		returneaza un vector cu obiectele de tip Carte din Repository sortate crescator in functie de autor
	*/
	vector<Carte> sorteazaAutor();


	/*
		returneaza un vector cu obiectele de tip Carte din Repository sortate crescator in functie de gen si an
	*/
	vector<Carte> sorteazaGenAn();
};


void testService();

void testSortari();

void testFiltrari();
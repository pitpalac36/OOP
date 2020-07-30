#pragma once
#include "Carte.h"
#include "Validator.h"
#include "Repository.h"
#include "DTO.h"
#include <functional>
using std::function;
#include <map>


class Service
{
private:
	CarteValidator& v;
	Repository& r;


	/*
		functie generica de filtrare
	*/
	List<Carte> filtreaza(function<bool(const Carte&)> fct);

	/*
		functie de sortare generica
	*/
	List<Carte> sortare(bool (*maiMicF)(const Carte&, const Carte&));

public:

	Service(Repository& repo, CarteValidator& val) : r{ repo }, v{ val }{}

	// nu se permite copierea unui obiect de tip Service
	Service(const Service& service) = delete;


	// returneaza vectorul de carti din Repository
	const List<Carte>& getAll() noexcept {
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
		returneaza o lista cu obiectele de tip Carte din Repository care au titlul < valoarea parametrului titlu
	*/
	List<Carte> filtreazaTitlu(string titlu);


	/*
		returneaza o lista cu obiectele de tip Carte din Repository care au anul < valoarea parametrului an
	*/
	List<Carte> filtreazaAn(int an);


	/*
		returneaza o lista cu obiectele de tip Carte din Repository sortate crescator in functie de titlu
	*/
	List<Carte> sorteazaTitlu();


	/*
		returneaza o lista cu obiectele de tip Carte din Repository sortate crescator in functie de autor
	*/
	List<Carte> sorteazaAutor();


	/*
		returneaza o lista cu obiectele de tip Carte din Repository sortate crescator in functie de gen si an
	*/
	List<Carte> sorteazaGenAn();


	vector<DTO> rapoarte();

};


void testService();

void testSortari();

void testFiltrari();

void testRapoarte();
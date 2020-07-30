#pragma once
#include "Carte.h"
#include "Repo.h"
#include <functional>
using std::function;
#include <map>
#include "Validator.h"
#include <memory>
#include "Undo.h"
#include "Cos.h"
using std::unique_ptr;


class DTO
{
private:
	int an;
	int nr;
public:
	DTO(int an, int nr) : an{an}, nr{nr}{}
	int getAn() {
		return an;
	};
	int getNr() {
		return nr;
	};
};



class Service
{
private:
	CarteValidator& v;
	AbstractRepo& r;
	Cos& cos;
	std::vector<unique_ptr<ActiuneUndo>> undoActions;

	/*
		functie generica de filtrare
	*/
	vector<Carte> filtreaza(function<bool(const Carte&)> fct);

	/*
		functie de sortare generica
	*/
	vector<Carte> sortare(bool (*maiMicF)(const Carte&, const Carte&));

public:

	Service(AbstractRepo& repo, CarteValidator& val, Cos& cos) : r{ repo }, v{ val }, cos{cos}{
	}


	// nu se permite copierea unui obiect de tip Service
	Service(const Service& service) = delete;


	// returneaza vectorul de carti din Repository
	vector<Carte> getAll(){
		return r.getAll();
	}


	/*
	sterge toate obiectele din vectorul cos
*/
	void golesteCos();

	/*
		adauga in vectorul cos primul obiect de tip Carte gasit in Repository care are titlul egal cu cel dat ca parametru
	*/
	void adaugaCos(string titlu);

	/*
		returneaza o copie a vectorului cos
	*/
	vector<Carte> getCos();

	/*
		goleste vectorul cos si adauga in el obiecte random din Repository; obiectele se pot repeta
		la final vectorul cos va avea dimensiunea egala cu parametrul dimensiune
	*/
	void genereazaCos(int dimensiune);

	void stergeCos(string titlu);

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
		- modifica in Repository un obiect de tip Carte care are titlu dat ca parametru
		- arunca ValidationException daca parametrul este invalid
	*/
	void schimbaCarte(const string& titlu, const string& autor, string& gen, int an);

	/*
		- face undo ultimei operatii efectuate daca aceasta este addCarte, stergeCarte sau schimbaCarte
		- arunca ServiceException daca nu se (mai) poate face undo 
	*/
	void undo();

	/*
		- salveaza obiectele din cos intr-un fisier specificat de tip "Comma Separated Values"
		- arunca ServiceException daca fisierul nu se poate crea / nu poate fi deschis
	*/
	void exportaCosCSV(string fisier) const;

	/*
		- salveaza obiectele din cos intr-un fisier specificat de tip HTML
		- arunca ServiceException daca fisierul nu se poate crea / nu poate fi deschis
	*/
	void exportaCosHTML(string fisier) const;


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


	vector<DTO> medie(int& m);
};


void testService();

void testSortari();

void testFiltrari();

void testCos();

void testRaport();

void testUndo();

void testExport();
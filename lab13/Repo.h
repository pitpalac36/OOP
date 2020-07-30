#pragma once
#include "Carte.h"
#include "AbstractRepo.h"
#include <vector>
#include <unordered_map>
using std::unordered_map;
using std::vector;

class Repo : public AbstractRepo
{
private:
	unordered_map<string, Carte> carti;

	bool exista(const Carte& c);

public:

	// constructorul default
	Repo() = default;


	// nu se permite copierea unui obiect de tip Repository
	Repo(const Repo& repo) = delete;


	/*
		- adauga un obiect de tip Carte in vectorul carti
		- arunca RepoException daca obiectul exista deja in vector
	*/
	void adauga(const Carte& c);


	/*
		- sterge obiectul c de tip Carte din vectorul carti
		- arunca RepoException daca obiectul nu exista in vector
	*/
	void sterge(const Carte& c);


	/*
		- cauta un obiect de tip Carte dupa campul titlu in dictionarul carti
		- returneaza prin referinta cartea gasita
		- arunca RepoException daca nu exista in vector niciun obiect cu titlul dat ca parametru
	*/
	Carte& cauta(string titlu);


	/*
		- foloseste metoda cauta ce returneaza o carte cu titlul si autorul date ca parametri
		- modifica campurile gen si anAparitie ale cartii gasite cu valorile parametrilor gen respectiv an
	*/
	void modifica(string titlu, string autor, string gen, int an);


	/*
		- returneaza prin referinta vectorul de carti
	*/
	std::vector<Carte> getAll();

	/*
		- returneaza nr cartilor din vector
	*/
	int size() const;


};

void testRepo();
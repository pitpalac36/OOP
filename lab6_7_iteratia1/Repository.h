#pragma once
#include "Carte.h"
#include "RepoException.h"
#include <vector>
using std::vector;

class Repository
{
private:
	vector<Carte> carti;

public:

	// constructorul default
	Repository() = default;


	// nu se permite copierea unui obiect de tip Repository
	Repository(const Repository& repo) = delete;


	/* 
		- adauga un obiect de tip Carte in vectorul carti
		- arunca RepoException daca obiectul exista deja in vector
	*/
	void adauga(const Carte& c);


	/*
		- sterge obiectul c de tip Carte din vectorul carti
		- arunca RepoException daca obiectul nu exista in vector
	*/
	void sterge(Carte& c);


	/*
		- cauta un obiect de tip Carte dupa campurile titlu si autor in vectorul carti
		- returneaza prin referinta cartea gasita
		- arunca RepoException daca nu exista in vector niciun obiect cu titlul si autorul date ca parametri
	*/
	Carte& cauta(string titlu, string autor);


	/*
		- foloseste metoda cauta ce returneaza o carte cu titlul si autorul date ca parametri
		- modifica campurile gen si anAparitie ale cartii gasite cu valorile parametrilor gen respectiv an
	*/
	void modifica(string titlu, string autor, string gen, int an);


	/*
		- returneaza prin referinta vectorul carti
	*/
	const vector<Carte>& getAll() const noexcept;
};

void testRepo();
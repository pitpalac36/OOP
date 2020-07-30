#pragma once
#include <vector>
using std::vector;
#include "Carte.h"
#include "AbstractRepo.h"

class Cos
{
private:
	vector<Carte> cos = vector<Carte>();
public:
	Cos() = default;

	/*
	sterge toate obiectele din vectorul cos
*/
	void golesteCos();


	void adaugaCos(const Carte& c);


	void stergeCos(string titlu);

	/*
		returneaza o copie a vectorului cos
	*/
	vector<Carte> getCos() const;

	/*
		goleste vectorul cos si adauga in el obiecte random din Repository; obiectele se pot repeta
		la final vectorul cos va avea dimensiunea egala cu parametrul dimensiune
	*/
	void genereazaCos(int dimensiune, AbstractRepo& repo);

};


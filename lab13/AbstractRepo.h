#pragma once
#include <string>
#include "Carte.h"
#include <unordered_map>
using std::unordered_map;

class AbstractRepo
{
private:
	unordered_map<std::string, Carte> carti;
public:

	virtual void adauga(const Carte& c) = 0;

	virtual void sterge(const Carte& c) = 0;

	virtual void modifica(string titlu, string autor, string gen, int an) = 0;

	virtual Carte& cauta(string titlu) = 0;

	virtual std::vector<Carte> getAll() = 0;

};


#include "Service.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <random>
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include "DTO.h"
using std::function;
using std::cout;
using std::string;
using std::iterator;
using std::map;


List<Carte> Service::filtreaza(function<bool(const Carte&)> fct)
{
	List<Carte> rez;
	for (const auto& carte : r.getAll()) {
		if (fct(carte)) {
			rez.push_back(carte);
		}
	}
	return rez;
}

List<Carte> Service::sortare(bool(*maiMicF)(const Carte&, const Carte&))
{
	List<Carte> l{ r.getAll() };
	for (size_t i = 0; i < r.size(); i++) {
		for (size_t j = i + 1; j < r.size(); j++) {
			if (!maiMicF(l[i], l[j])) {
				Carte aux = l[i];
				l[i] = l[j];
				l[j] = aux;
			}
		}
	}
	return l;
}

List<Carte> Service::filtreazaTitlu(string titlu) {
	return filtreaza([titlu](const Carte& c) {
		return c.getTitlu() < titlu;
	});
}

List<Carte> Service::filtreazaAn(int an) {
	return filtreaza([an](const Carte& c) {
		return c.getAn() < an;
	});
}

List<Carte> Service::sorteazaTitlu()
{
	return sortare(cmpTitlu);
}

List<Carte> Service::sorteazaAutor()
{
	return sortare(cmpAutor);
}

List<Carte> Service::sorteazaGenAn()
{
	return sortare(cmpAnGen);
}

vector<DTO> Service::rapoarte()
{
	List<Carte> lista = this->r.getAll();
	map<string, int> dict;
	map<string, int>::iterator it;
	for (const Carte& c : lista) {
		it = dict.find(c.getGen());
		if (it == dict.end())
			dict.insert(make_pair(c.getGen(), 1));
		else dict[c.getGen()] ++;
	}
	vector<DTO> dtos;
	for (it = dict.begin(); it != dict.end(); it++)
		dtos.push_back(DTO{ it->first, it->second });
	return dtos;
}


void Service::addCarte(const string& titlu, const string& autor, const string& gen, int an)
{
	Carte c{ titlu,autor,gen,an };
	v.valideazaCarte(c);
	r.adauga(c);
}

void Service::stergeCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ titlu,autor,gen,an };
	v.valideazaCarte(c);
	r.sterge(c);
}

void Service::schimbaCarte(const string& titlu, const string& autor, string& gen, int an)
{
	Carte c{ titlu,autor,gen,an };
	v.valideazaCarte(c);
	r.modifica(c.getTitlu(), c.getAutor(), gen, an);
}


void testService()
{
	Repository r;
	CarteValidator v;
	Service serv{ r,v };
	assert(serv.getAll().size() == 0);
	try {
		serv.addCarte("qs", "dxc", "df", 100);
		serv.addCarte("", "", "", 0);
		assert(false);
	}
	catch (ValidationException ex) {
		assert(true);
	}
	assert(serv.getAll().size() == 1);
	try {
		serv.stergeCarte("x", "y", "z", 1940);
		assert(false);
	}
	catch (RepoException ex) {
		assert(true);
	}
	string gen = "gen";
	serv.schimbaCarte("qs", "dxc", gen, 2018);
	auto elem = serv.getAll();
	assert(elem[0].getGen() == gen);
	assert(elem[0].getAn() == 2018);
	serv.stergeCarte("qs", "dxc", gen, 2018);
	assert(serv.getAll().size() == 0);
}


void testSortari() {
	Repository r;
	CarteValidator v;
	Service s{ r,v };
	vector<Carte> sorted;
	int j = 99;
	for (int i = 0; i < 10; i++) {
		r.adauga(Carte{ "t" + std::to_string(i % 2), "a" + std::to_string(j), "g", j });
		j--;
	}
	List<Carte> t = s.sorteazaTitlu();
	for (int i = 0; i < 5; i++)
		assert(t[i].getTitlu() == "t0");
	for (int i = 5; i < 10; i++)
		assert(t[i].getTitlu() == "t1");

	t = s.sorteazaAutor();
	j = 90;
	for (int i = 0; i < 9; i++) {
		assert(t[i].getAutor() == ("a" + std::to_string(j)));
		j++;
	}
	t = s.sorteazaGenAn();
	j = 90;
	for (int i = 0; i < 9; i++) {
		assert(t[i].getAn() == j);
		j++;
	}
}


void testFiltrari() {
	// filtreaza titlu ; filtreaza an
	Repository r;
	CarteValidator v;
	Service s{ r,v };
	List<Carte> sorted;
	int j = 99;
	for (int i = 0; i < 10; i++) {
		r.adauga(Carte{ "t" + std::to_string(i), "a" + std::to_string(j), "g", j });
		j--;
	}
	List<Carte> t = s.filtreazaTitlu("a");
	assert(t.size() == 0);
	t = s.filtreazaTitlu("z");
	assert(t.size() == 10);
	t = s.filtreazaTitlu("t9");
	assert(t.size() == 9);
	t = s.filtreazaAn(100);
	assert(t.size() == 10);
	t = s.filtreazaAn(10);
	assert(t.size() == 0);
}

void testRapoarte()
{
	DTO dto1 = DTO{ "drama", 1 };
	assert(dto1.getContor() == 1);
	assert(dto1.getGen() == "drama");
	Repository r;
	CarteValidator v;
	Service s{ r,v };
	for (int i = 0; i < 5; i++) {
		r.adauga(Carte{ "titlu" + std::to_string(i), "autor" + std::to_string(i), "horror", 2020});
	}
	assert(s.rapoarte().size() == 1);
	assert(s.rapoarte().at(0).getGen() == "horror");
	assert(s.rapoarte().at(0).getContor() == 5);
}

#include "Service.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <random>
#include <iostream>
using std::function;
using std::cout;


vector<Carte> Service::filtreaza(function<bool(const Carte&)> fct)
{
	vector<Carte> rez;
	for (const auto& carte : r.getAll()) {
		if (fct(carte)) {
			rez.push_back(carte);
		}
	}
	return rez;
}

vector<Carte> Service::filtreazaTitlu(string titlu) {
	return filtreaza([titlu](const Carte& c) {
		return c.getTitlu() < titlu;
	});
}

vector<Carte> Service::filtreazaAn(int an) {
	return filtreaza([an](const Carte& c) {
		return c.getAn() < an;
	});
}

vector<Carte> Service::sorteazaTitlu()
{
	auto copie = r.getAll();
	std::sort(copie.begin(), copie.end(), cmpTitlu);
	return copie;
}

vector<Carte> Service::sorteazaAutor()
{
	auto copie = r.getAll();
	std::sort(copie.begin(), copie.end(), cmpAutor);
	return copie;
}

vector<Carte> Service::sorteazaGenAn()
{
	auto copie = r.getAll();
	std::sort(copie.begin(), copie.end(), cmpAnGen);
	return copie;
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
	assert(serv.getAll().at(0).getGen() == gen);
	assert(serv.getAll().at(0).getAn() == 2018);
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
	vector<Carte> t = s.sorteazaTitlu();
	for (int i = 0; i < 5; i++)
		assert(t.at(i).getTitlu() == "t0");
	for (int i = 5; i < 10; i++)
		assert(t.at(i).getTitlu() == "t1");

	auto rng = std::default_random_engine{};
	std::shuffle(std::begin(t), std::end(t), rng);

	t = s.sorteazaAutor();
	j = 90;
	for (int i = 0; i < 9; i++) {
		assert(t.at(i).getAutor() == ("a" + std::to_string(j)));
		j++;
	}
	t = s.sorteazaGenAn();
	j = 90;
	for (int i = 0; i < 9; i++) {
		assert(t.at(i).getAn() == j);
		j++;
	}
}


void testFiltrari() {
	// filtreaza titlu ; filtreaza an
	Repository r;
	CarteValidator v;
	Service s{ r,v };
	vector<Carte> sorted;
	int j = 99;
	for (int i = 0; i < 10; i++) {
		r.adauga(Carte{ "t" + std::to_string(i), "a" + std::to_string(j), "g", j });
		j--;
	}
	vector<Carte> t = s.filtreazaTitlu("a");
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
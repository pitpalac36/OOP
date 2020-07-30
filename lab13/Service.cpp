#include "Service.h"
#include "ServiceException.h"
#include <cassert>
#include <algorithm>
#include <functional>
#include <random>
#include <iostream>
#include <string>
#include <iterator>
#include <map>
#include<random>
#include <fstream>
#include "RepoException.h"
using std::function;
using std::cout;
using std::string;
using std::iterator;
using std::map;
#include <numeric>
#include "fileUtils.h"


vector<Carte> Service::filtreaza(function<bool(const Carte&)> fct)
{
	vector<Carte> rez;
	vector<Carte> all = r.getAll();
	std::copy_if(all.begin(), all.end(), back_inserter(rez), fct);
	return rez;
}

vector<Carte> Service::sortare(bool(*maiMicF)(const Carte&, const Carte&))
{
	vector<Carte> rez{ r.getAll() };
	std::sort(rez.begin(), rez.end(), maiMicF);
	return rez;
}

void Service::golesteCos()
{
	vector<Carte> allCos = cos.getCos();
	cos.golesteCos();
	notify();
}

void Service::adaugaCos(string titlu)
{
	auto c = r.cauta(titlu);
	cos.adaugaCos(c);
	undoActions.push_back(std::make_unique<UndoAdaugareCos>(cos, c));
	notify();
}


vector<Carte> Service::getCos()
{
	return cos.getCos();
}

void Service::genereazaCos(int dimensiune)
{
	cos.genereazaCos(dimensiune, r);
	notify();
}

void Service::stergeCos(string titlu)
{
	cos.stergeCos(titlu);
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
	return sortare(cmpTitlu);
}

vector<Carte> Service::sorteazaAutor()
{
	return sortare(cmpAutor);
}

vector<Carte> Service::sorteazaGenAn()
{
	return sortare(cmpAnGen);
}



vector<DTO> Service::medie(int& m)
{
	vector<Carte> all = r.getAll();

	map<int, int> count;
	map<int, int>::iterator iter;

	for (int i = 0; i < (int)all.size(); i++)
	{
		iter = count.find(all[i].getAn());
		if (iter == count.end())
			count.insert(std::make_pair(all[i].getAn(), 1));
		else
			count[all[i].getAn()]++;
	}

	m = 0;
	m = std::accumulate(all.begin(), all.end(), m, [](int nr, Carte carte) {
		return nr + carte.getAn();
	});

	m /= all.size();   // media anilor pt cartile din repo

	vector<DTO> dtos;
	for (iter = count.begin(); iter != count.end(); ++iter)
	{
		DTO obj{ iter->first, iter->second };
		dtos.push_back(obj);
	}
	return dtos;
}


void Service::addCarte(const string& titlu, const string& autor, const string& gen, int an)
{
	Carte c{ titlu,autor,gen,an };
	v.valideazaCarte(c);
	r.adauga(c);
	undoActions.push_back(std::make_unique<UndoAdauga>(r, c));
	notify();
}

void Service::stergeCarte(const string& titlu, const string& autor, const string& gen, int an) {
	Carte c{ titlu,autor,gen,an };
	v.valideazaCarte(c);
	r.sterge(c);
	undoActions.push_back(std::make_unique<UndoSterge>(r, c));
	notify();
}

void Service::schimbaCarte(const string& titlu, const string& autor, string& gen, int an)
{
	Carte c{ titlu,autor,gen,an };
	auto c1 = r.cauta(titlu);
	v.valideazaCarte(c);
	r.modifica(c.getTitlu(), autor, gen, an);
	undoActions.push_back(std::make_unique<UndoModifica>(r, c1));
	notify();
}

void Service::undo()
{
	if (undoActions.empty())
		throw ServiceException("Nu se poate face undo!");
	undoActions.back()->doUndo();
	undoActions.pop_back();
	notify();
}


void Service::exportaCosCSV(std::string fisier) const {
	exportToCSV(fisier, cos.getCos());
}

void Service::exportaCosHTML(std::string fisier) const {
	exportToHTML(fisier, cos.getCos());
}


void testService()
{
	Repo r;
	CarteValidator v;
	Cos cos;
	Service serv{ r,v, cos };
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

	Repo r;
	CarteValidator v;
	Cos cos;
	Service s{ r,v, cos };
	vector<Carte> sorted;
	int j = 99;
	for (int i = 0; i < 10; i++) {
		r.adauga(Carte{ "t" + std::to_string(j), "a" + std::to_string(i % 2), "g", j });
		j--;
	}
	vector<Carte> t = s.sorteazaAutor();
	for (int i = 0; i < 5; i++)
		assert(t[i].getAutor() == "a0");
	for (int i = 5; i < 10; i++)
		assert(t[i].getAutor() == "a1");

	t = s.sorteazaTitlu();
	j = 90;
	for (int i = 0; i < 9; i++) {
		assert(t[i].getTitlu() == ("t" + std::to_string(j)));
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
	Repo r;
	CarteValidator v;
	Cos cos;
	Service s{ r,v,cos };
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


void testCos()
{
	Repo r;
	CarteValidator v;
	Cos cos;
	Service s{ r,v,cos };
	vector<Carte> sorted;
	int j = 99;
	for (int i = 0; i < 10; i++) {
		r.adauga(Carte{ "t" + std::to_string(i), "a" + std::to_string(j), "g", j });
		j--;
	}
	s.adaugaCos("t5");
	assert(s.getCos().size() == 1);
	try {
		s.adaugaCos("t10");
		assert(false);
	}
	catch (RepoException ex) {
		assert(true);
	}
	s.genereazaCos(10);
	assert(s.getCos().size() == 10);

	vector<Carte> copieRepo = s.getAll();
	for (auto c : s.getCos()) {
		auto it = find(copieRepo.begin(), copieRepo.end(), c);
		assert(it != copieRepo.end());
	}
	s.golesteCos();
	assert(s.getCos().size() == 0);
	try {
		s.golesteCos();
		assert(false);
	}
	catch (ServiceException ex) {
		assert(true);
	}
	s.adaugaCos("t5");
	try {
		s.adaugaCos("t5");
		assert(false);
	}
	catch (ServiceException ex) {
		assert(true);
	}
	s.stergeCos("t5");
	assert(cos.getCos().size() == 0);
}

void testRaport()
{
	DTO dto{ 1984, 3 };
	assert(dto.getAn() == 1984);
	assert(dto.getNr() == 3);

	Repo r;
	CarteValidator v;
	Cos cos;
	Service s{ r,v, cos };
	for (int i = 0; i < 10; i++)
		r.adauga(Carte{ "t" + std::to_string(i), "a" + std::to_string(i), "drama", i + 1900 });
	int m = 0;
	vector<DTO> dtos = s.medie(m);
	assert(dtos.size() == 10);
	for (int i = 0; i < 10; i++) {
		assert(dtos[i].getAn() == i + 1900);
		assert(dtos[i].getNr() == 1);
	}
	for (int i = 0; i < 5; i++)
		r.modifica("t" + std::to_string(i), "a" + std::to_string(i), "drama", 1984);
	dtos = s.medie(m);
	assert(dtos.size() == 6);
	assert(dtos[5].getAn() == 1984);
	assert(dtos[5].getNr() == 5);
	for (int i = 0; i < 5; i++) {
		assert(dtos[i].getAn() != 1984);
		assert(dtos[i].getNr() == 1);
	}
}

void testUndo()
{
	Repo r;
	CarteValidator v;
	Cos cos;
	Service s{ r,v, cos };
	string gen = "thriller";
	for (int i = 0; i < 10; i++) {
		s.addCarte("t" + std::to_string(i), "a" + std::to_string(i), "drama", 1900 + i);
		s.schimbaCarte("t" + std::to_string(i), "a" + std::to_string(i), gen, 1910 + i);
	}
	for (int i = 10; i > 0; i--) {
		s.undo();  // undo la modificare
		assert(r.getAll().at(i - 1).getGen() == "drama");  // genul initial
		assert(r.getAll().at(i - 1).getAn() == 1900 + i - 1);  // anul initial
		assert(r.size() == i);
		s.undo();  // undo la adaugare
		assert(r.size() == i - 1);
	}
	try {
		s.undo();
		assert(false);
	}
	catch (ServiceException ex) {
		assert(true);
	}
	for (int i = 0; i < 10; i++) {
		s.addCarte("t" + std::to_string(i), "a" + std::to_string(i), "comedie", 1900 + i);
		s.stergeCarte("t" + std::to_string(i), "a" + std::to_string(i), "comedie", 1900 + i);
		assert(r.size() == i);
		s.undo();  // undo stergere
		assert(r.size() == i + 1);
	}
	s.addCarte("titlu", "autor", "comedie", 1987);
	s.addCarte("poezii", "autor", "drama", 1966);
	s.adaugaCos("titlu");
	s.adaugaCos("poezii");
	s.undo();
	assert(s.getCos().size() == 1);
	s.undo();
	assert(s.getCos().size() == 0);
}

void testExport()
{
	Repo r;
	CarteValidator v;
	Cos cos;
	Service s{ r,v, cos };
	string line;
	int i = 0;
	s.addCarte("titlu", "autor", "gen", 1900);
	s.genereazaCos(5);
	s.exportaCosCSV("numefisier");
	s.exportaCosHTML("altnumefisier");
	std::ifstream in("cos\\numefisier.csv");
	while (std::getline(in, line))
	{
		i++;
		string virgula = ",";
		assert(line.substr(0, line.find(virgula)) == "titlu");
		line.erase(0, line.find(virgula) + virgula.length());
		assert(line.substr(0, line.find(virgula)) == "autor");
		line.erase(0, line.find(virgula) + virgula.length());
		assert(line.substr(0, line.find(virgula)) == "gen");
		line.erase(0, line.find(virgula) + virgula.length());
		assert(line.substr(0, line.find(virgula)) == "1900");
	}
	assert(i == 5);
	in.close();
	std::ifstream in2("cos\\altnumefisier.html");
	std::getline(in2, line);
	assert(line == "<html><body>");
	std::getline(in2, line);
	for (i = 0; i < 5; i++)
	{
		std::getline(in2, line);
		assert(line == "<tr>");
		std::getline(in2, line);
		assert(line == "<td>titlu</td>");
		std::getline(in2, line);
		assert(line == "<td>autor</td>");
		std::getline(in2, line);
		assert(line == "<td>gen</td>");
		std::getline(in2, line);
		assert(line == "<td>1900</td>");
		std::getline(in2, line);
		assert(line == "</tr>");
	}
	std::getline(in2, line);
	assert(line == "</table>");
	std::getline(in2, line);
	assert(line == "</body></html>");
	in2.close();
}

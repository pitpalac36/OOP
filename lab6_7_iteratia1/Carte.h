#pragma once
#include <string>
using std::string;

class Carte
{
private:
	string titlu;
	string autor;
	string gen;
	int anAparitie;

public:

	// constructor default
	Carte() = default;


	Carte(string t, string a, string g, int an): titlu{t}, autor{a}, gen{g}, anAparitie{an}{}


	// constructor de copiere
	Carte(const Carte& c) : titlu{c.titlu}, autor{c.autor}, gen{c.gen}, anAparitie{c.anAparitie}{}


	/* 
		Returneaza titlul entitatii curente
	*/
	string getTitlu() const {
		return titlu;
	}


	/*
		Returneaza autorul entitatii curente
	*/
	string getAutor() const {
		return autor;
	}


	/*
		Returneaza genul entitatii curente
	*/
	string getGen() const {
		return gen;
	}


	/*
		Returneaza anul entitatii curente
	*/
	int getAn() const {
		return anAparitie;
	}


	/*
		Seteaza valoarea titlului entitatii curente
	*/
	void setTitlu(string t) {
		titlu = t;
	}


	/*
		Seteaza valoarea autorului entitatii curente
	*/
	void setAutor(string a) {
		autor = a;
	}


	/*
		Seteaza valoarea genului entitatii curente
	*/
	void setGen(string g) {
		gen = g;
	}


	/*
		Seteaza valoarea anului entitatii curente
	*/
	void setAn(int an) {
		anAparitie = an;
	}


	/*
		Compara egalitatea campurilor entitatii curente cu cele ale unei entitati date ca parametru
	*/
	bool operator==(const Carte& other) {
		return (autor == other.autor && gen == other.gen && anAparitie == other.anAparitie && titlu == other.titlu);
	}
};


/*
	Compara titlurile a doua entitati de tip Carte date ca parametri; 
	- returneaza true daca titlul primei entitati este dpdv lexicografic inaintea titlului celeilalte entitati sau daca sunt egale
	- returneaza false altfel
*/
bool cmpTitlu(const Carte& c1, const Carte& c2);


/*
	Compara autorii a doua entitati de tip Carte date ca parametri;
	- returneaza true daca autorul primei entitati este dpdv lexicografic inaintea autorului celeilalte entitati sau daca sunt egali
	- returneaza false altfel
*/
bool cmpAutor(const Carte& c1, const Carte& c2);


/*
	Compara anii si genurile a doua entitati de tip Carte date ca parametri;
	- returneaza true daca anul primei entitati este mai mic decat al celeilalte;
	- returneaza true daca anii celor doua entitati sunt egali dar genul primeia este inaintea genului celeilalte dpdv lexicografic
	- returneaza false altfel
*/
bool cmpAnGen(const Carte& c1, const Carte& c2);


void testCarte();
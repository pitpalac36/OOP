#include "Carte.h"
#include <cassert>


bool cmpTitlu(const Carte& c1, const Carte& c2)
{
	return c1.getTitlu() < c2.getTitlu();
}

bool cmpAutor(const Carte& c1, const Carte& c2)
{
	return c1.getAutor() < c2.getAutor();
}

bool cmpAnGen(const Carte& c1,const Carte& c2)
{
	return (c1.getAn() < c2.getAn()) || (c1.getAn() == c2.getAn() && c1.getGen().compare(c2.getGen()) <= 0);
}

void testCarte()
{
	Carte c{ "dune", "asimov", "SF", 1980 };
	assert(c.getTitlu() == "dune");
	assert(c.getAutor() == "asimov");
	assert(c.getGen() == "SF");
	assert(c.getAn() == 1980);
	Carte c1{ "1984", "orwell", "drama", 1960 };
	assert(cmpTitlu(c,c1) == false);
	assert(cmpAutor(c,c1) == true);
	assert(cmpAnGen(c,c1) == false);
	c.setAn(2000);
	c.setGen("geeen");
	assert(c.getGen() == "geeen");
	assert(c.getAn() == 2000);
}

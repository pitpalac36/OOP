#include "Repository.h"
#include "cassert"

bool Repository::exista(const Carte& c)
{
	try {
		cauta(c.getTitlu(), c.getAutor());
		return true;
	}
	catch (RepoException&) {
		return false;
	}
}

void Repository::adauga(const Carte& c)
{
	if (exista(c))
		throw RepoException("Exista deja o carte cu aceste date!");
	carti.push_back(c);
}

void Repository::sterge(Carte& c)
{
	if (!exista(c))
		throw RepoException("Nu exista nicio carte cu aceste date!");
	carti.erase(c);
}

Carte& Repository::cauta(string titlu, string autor)
{
	for (auto& c : carti)
		if (c.getTitlu() == titlu && c.getAutor() == autor)
			return c;
	throw RepoException("Nu exista nicio carte cu titlul " + titlu + " si autorul " + autor);
}


void Repository::modifica(string titlu, string autor, string gen, int an)
{
	auto& cautata = cauta(titlu, autor);
	cautata.setGen(gen);
	cautata.setAn(an);
}

const List<Carte>& Repository::getAll() const noexcept
{
	return carti;
}

int Repository::size() const noexcept
{
	return carti.size();
}


void testRepo()
{
	Repository r;
	r.adauga(Carte{ "t1","a1","g1",1900 });
	r.adauga(Carte{ "t2","a2","g2",1900 });
	assert(r.size() == 2);
	try {
		try {
			r.cauta("t1", "a1");
		}
		catch (RepoException) {
			assert(false);
		}
		r.cauta("t5", "a2");
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	Carte c3{ "t3","a3","g1",1900 };
	try {
		r.sterge(c3);
		assert(false);
	}
	catch (RepoException) {
		assert(true);
	}
	assert(r.size() == 2);
	c3.setTitlu("t1");
	c3.setAutor("a1");
	r.sterge(c3);
	assert(r.size() == 1);

	r.modifica("t2", "a2", "ggg", 2000);
	auto elem = r.getAll();
	assert(elem[0].getGen() == "ggg");
	assert(elem[0].getAn() == 2000);
	r.adauga(Carte{ "t10","a10","g10",2010 });
	r.adauga(Carte{ "t20","a20","g20",1900 });
	assert(r.getAll().size() == 3);
	Carte c2;
	c2.setTitlu("t20");
	c2.setAutor("a20");
	c2.setGen("g20");
	c2.setAn(1900);
	r.sterge(c2);
	assert(r.size() == 2);
}
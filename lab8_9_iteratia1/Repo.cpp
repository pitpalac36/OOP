#include "Repo.h"
#include "cassert"
#include <algorithm>
#include "RepoException.h"
using std::vector;
using std::transform;


bool Repo::exista(const Carte& c)
{
	std::unordered_map<string, Carte>::const_iterator it = carti.find(c.getTitlu());
	return !(it == carti.end());
}

void Repo::adauga(const Carte& c)
{
	if (exista(c))
		throw RepoException("Exista deja o carte cu aceste date!");
	carti.insert(std::make_pair<>(c.getTitlu(), c));
}

void Repo::sterge(const Carte& c)
{
	if (!exista(c))
		throw RepoException("Nu exista nicio carte cu aceste date!");
	carti.erase(c.getTitlu());
}

Carte& Repo::cauta(string titlu, string autor)
{
	auto it = carti.find(titlu);
	if (it == carti.end())
		throw RepoException("Nu exista nicio carte cu aceste date!");
	return (*it).second;
}


void Repo::modifica(string titlu, string autor, string gen, int an)
{
	auto& cautata = cauta(titlu, autor);
	cautata.setGen(gen);
	cautata.setAn(an);
}

int Repo::size() const
{
	return carti.size();
}


vector<Carte> Repo::getAll()
{
	vector<Carte> deReturnat{carti.size()};
	if (carti.empty() == true)
		return deReturnat;
	transform(carti.begin(), carti.end(), deReturnat.begin(), [](auto c) {
		return c.second;
	});
	return deReturnat;
}


void testRepo()
{
	Repo r;
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
	try {
		r.adauga(Carte{ "t20","a20","g20",1900 });
		assert(false);
	}
	catch (RepoException e) {
		assert(true);
	}
	assert(r.getAll().size() == 3);
	Carte c2;
	c2.setTitlu("t20");
	c2.setAutor("a20");
	c2.setGen("g20");
	c2.setAn(1900);
	r.sterge(c2);
	assert(r.size() == 2);
}

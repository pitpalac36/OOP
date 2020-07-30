#include "Repository.h"
#include "cassert"
void Repository::adauga(const Carte& c)
{
	if (std::find(carti.begin(), carti.end(), c) != carti.end())
		throw RepoException("Exista deja o carte cu aceste date!");
	carti.push_back(c);
}

void Repository::sterge(Carte& c)
{
	vector<Carte>::iterator poz = std::find(carti.begin(), carti.end(), c);
	if( poz != carti.end())
		carti.erase(poz);
	else
		throw RepoException("Nu exista nicio carte cu aceste date!");
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

const vector<Carte>& Repository::getAll() const noexcept
{
	return carti;
}

void testRepo()
{
	Repository r;
	r.adauga(Carte{ "t1","a1","g1",1900 });
	r.adauga(Carte{ "t2","a2","g2",1900 });
	assert(r.getAll().size() == 2);
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
	assert(r.getAll().size() == 2);
	c3.setTitlu("t1");
	c3.setAutor("a1");
	r.sterge(c3);
	assert(r.getAll().size() == 1);

	// r.getAll().at(0)  = Carte{ "t2","a2","g2",1900 }
	r.modifica("t2", "a2", "ggg", 2000);
	assert(r.getAll().at(0).getGen() == "ggg");
	assert(r.getAll().at(0).getAn() == 2000);
}
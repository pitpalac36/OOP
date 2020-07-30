#include "Cos.h"
#include "ServiceException.h"
#include <random>

void Cos::golesteCos()
{
	if (cos.size() == 0)
		throw ServiceException("Cosul este deja gol!");
	cos.clear();
}


void Cos::adaugaCos(const Carte& c)
{
	for (auto carte : cos) {
		if (carte == c)
			throw ServiceException("Cartea exista deja in cos");
	}
	cos.push_back(c);
}

void Cos::stergeCos(string titlu)
{
	auto it = std::find_if(cos.begin(), cos.end(), [titlu](Carte c) {
		return c.getTitlu() == titlu;
	});
	cos.erase(it);
}


vector<Carte> Cos::getCos() const
{
	return cos;
}

void Cos::genereazaCos(int dimensiune, AbstractRepo& repo)
{
	std::mt19937 mt{ std::random_device{}() };
	std::uniform_int_distribution<> dist(0, repo.getAll().size() - 1);
	cos.clear();

	while ((int)cos.size() < dimensiune) {
		int rndNr = dist(mt); // numar aleator intre [0, repo.size() - 1]
		cos.push_back(repo.getAll().at(rndNr));
	}
}

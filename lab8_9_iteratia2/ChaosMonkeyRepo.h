#pragma once
#include "Repo.h"
#include "RepoException.h"


class ChaosMonkeyRepo : public Repo
{
private:
	float p;

	void throwWithProbability() {
		float prob = (float)rand() / RAND_MAX;
		if (prob < p)
			throw RepoException("! Chaos Monkey Exception !");
	}

public:
	ChaosMonkeyRepo(float p) : p{p}{}


	ChaosMonkeyRepo(const Repo& repo) = delete;


	void adauga(const Carte& c) override {
		throwWithProbability();
		Repo::adauga(c);
	}


	void sterge(const Carte& c) override {
		throwWithProbability();
		Repo::sterge(c);
	}


	Carte& cauta(string titlu) override {
		throwWithProbability();
		return Repo::cauta(titlu);
	}


	void modifica(string titlu, string autor, string gen, int an) override {
		throwWithProbability();
		Repo::modifica(titlu, autor, gen, an);
	}

	void setProbability(float p) {
		this->p = p;
	}
};


void testChaosMonkeyRepo();
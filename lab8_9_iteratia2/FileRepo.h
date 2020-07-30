#pragma once
#include "Repo.h"


class FileRepo : public Repo
{
private:
	string filename;

	void writeToFile();

	void loadFromFile();

public:
	FileRepo(const string& filename) : filename{ filename } {
		loadFromFile();
	}

	FileRepo(const FileRepo& other) = delete;

	void adauga(const Carte& c) override {
		Repo::adauga(c);
		writeToFile();
	}

	void modifica(string titlu, string autor, string gen, int an) override {
		Repo::modifica(titlu, autor, gen, an);
		writeToFile();
	}

	void sterge(const Carte& c) override {
		Repo::sterge(c);
		writeToFile();
	}

};

void testFileRepo();
#include "FileRepo.h"
#include <fstream>
#include <cassert>
#include <iostream>
#include "RepoException.h"

void FileRepo::writeToFile()
{
	std::ofstream out(filename);
	vector<Carte> all = Repo::getAll();
	vector<Carte>::iterator it;
	for (it = all.begin(); it < all.end(); it++) {
		auto str = (*it).getTitlu() + " " + (*it).getAutor() + " " + (*it).getGen() + " " + std::to_string((*it).getAn()) + "\n";
		out << str;
	}
	out.close();
}

void FileRepo::loadFromFile()
{
	std::ifstream in(filename);
	string titlu, autor, gen;
	int an;
	while (in >> titlu >> autor >> gen >> an)
		Repo::adauga(Carte{ titlu.c_str(), autor.c_str(), gen.c_str(), an });
	in.close();
}

void testFileRepo()
{
	std::ofstream out("test\\testulet.txt", std::ios::trunc);
	FileRepo repo("test\\testulet.txt");
	assert(repo.size() == 0);
	for (int i = 0; i < 10; i++)
		repo.adauga(Carte{ "titlu" + std::to_string(i), "autor" + std::to_string(i), "drama", 1984 });
	assert(repo.size() == 10);
	std::ifstream in("test\\testulet.txt");
	string line;
	int i = 0;
	while (std::getline(in, line)) {
		string delimitator = " ";
		assert(line.substr(0, line.find(delimitator)) == "titlu" + std::to_string(i));
		line.erase(0, line.find(delimitator) + delimitator.length());
		assert(line.substr(0, line.find(delimitator)) == "autor" + std::to_string(i));
		line.erase(0, line.find(delimitator) + delimitator.length());
		assert(line.substr(0, line.find(delimitator)) == "drama");
		line.erase(0, line.find(delimitator) + delimitator.length());
		assert(line.substr(0, line.find(delimitator)) == "1984");
		i++;
	}
	in.close();
	FileRepo repo2("test\\testulet.txt");
	assert(repo2.size() == 10);
	for (int i = 0; i < 5; i++)
		repo2.sterge(Carte{ "titlu" + std::to_string(i), "autor" + std::to_string(i), "drama", 1984 });
	assert(repo2.size() == 5);
	for (int i = 5; i < 10; i++)
		repo2.modifica("titlu" + std::to_string(i), "autor" + std::to_string(i), "comedie", 1990);

	std::ifstream in2("test\\testulet.txt");
	i = 5;
	while (std::getline(in2, line)) {
		string delimitator = " ";
		assert(line.substr(0, line.find(delimitator)) == "titlu" + std::to_string(i));
		line.erase(0, line.find(delimitator) + delimitator.length());
		assert(line.substr(0, line.find(delimitator)) == "autor" + std::to_string(i));
		line.erase(0, line.find(delimitator) + delimitator.length());
		assert(line.substr(0, line.find(delimitator)) == "comedie");
		line.erase(0, line.find(delimitator) + delimitator.length());
		assert(line.substr(0, line.find(delimitator)) == "1990");
		i++;
	}
	in2.close();
}

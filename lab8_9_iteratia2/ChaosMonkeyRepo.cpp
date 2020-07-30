#include "ChaosMonkeyRepo.h"
#include <cassert>
#include <iostream>

void testChaosMonkeyRepo()
{
	auto contor = 0;
	ChaosMonkeyRepo repo{ 0.5 };  // jumatate dintre operatii vor arunca exceptie
	for (int i = 0; i < 20; i++)
		try {
			repo.adauga(Carte{ "t" + std::to_string(i), "a" + std::to_string(i), "drama", 1900 + i });
		}
		catch (RepoException&) {
			contor++;
		}
		std::cout << "pt p = 0.5 s-a aruncat exceptie de " << contor << " ori din 20\n";
	
	repo.setProbability(0); // nu va arunca exceptie speciala niciodata
	contor = 0;
	for (int i = 20; i < 35; i++)
		try {
		repo.adauga(Carte{ "t" + std::to_string(i), "a" + std::to_string(i), "drama", 1900 + i });
		repo.modifica("t" + std::to_string(i), "Marin Preda", "drama", 1970);
		}
		catch (RepoException&) {
			contor++;
		}
	std::cout << "pt p = 0 s-a aruncat exceptie de " << contor << " ori din 15\n";

	repo.setProbability(1); // se va arunca exceptie speciala la fiecare operatie
	contor = 0;
	for (int i = 20; i < 35; i++)
		try {
		auto c = repo.cauta( "t" + std::to_string(i));
	}
	catch (RepoException&) {
		contor++;
	}
	std::cout << "pt p = 1 s-a aruncat exceptie de " << contor << " ori din 15\n\n";

	auto dim = repo.size();
	for (auto& c : repo.getAll()) {
		try {
			repo.sterge(c);
			assert(false);
		}
		catch (RepoException&) {
			assert(true);
		}
	}
	repo.setProbability(0);
	for (auto& c : repo.getAll())
		repo.sterge(c);
}

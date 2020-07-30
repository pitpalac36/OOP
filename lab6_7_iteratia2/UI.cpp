#include "UI.h"
#include <iostream>
#include <functional>
using std::cout;
using std::cin;
using std::function;

void UI::adaugaCarte()
{
	cout << std::endl;
	string titlu, autor, gen;
	int anAparitie;
	cout << "Titlu : ";
	cin >> titlu;
	cout << "Autor : ";
	cin >> autor;
	cout << "Gen : ";
	cin >> gen;
	cout << "An aparitie : ";
	cin >> anAparitie;
	service.addCarte(titlu, autor, gen, anAparitie);
}

void UI::tipareste(const List<Carte>& carti)
{
	cout << std::endl;
	for (const auto& c : carti)
		cout << c.getTitlu() << " " << c.getAutor() << " " << c.getGen() << " " << c.getAn() << "\n";
	cout << std::endl;

}

void UI::stergeCarte()
{
	cout << std::endl;
	string titlu, autor, gen;
	int anAparitie;
	cout << "Titlu : ";
	cin >> titlu;
	cout << "Autor : ";
	cin >> autor;
	cout << "Gen : ";
	cin >> gen;
	cout << "An aparitie : ";
	cin >> anAparitie;
	service.stergeCarte(titlu, autor, gen, anAparitie);
}

void UI::schimbaCarte()
{
	cout << std::endl;
	string titlu, autor, gen;
	int anAparitie;
	cout << "Titlu : ";
	cin >> titlu;
	cout << "Autor : ";
	cin >> autor;
	cout << "Gen nou : ";
	cin >> gen;
	cout << "An aparitie nou : ";
	cin >> anAparitie;
	service.schimbaCarte(titlu, autor, gen, anAparitie);
}

void UI::filtrareTitlu()
{
	cout << std::endl;
	string titlu;
	cout << "Titlu maxim dpdv lexicografic : ";
	cin >> titlu;
	tipareste(service.filtreazaTitlu(titlu));
}

void UI::filtrareAn()
{
	cout << std::endl;
	int an;
	cout << "Anul maxim de aparitie : ";
	cin >> an;
	tipareste(service.filtreazaAn(an));
}

void UI::rapoarte()
{
	vector<DTO> deAfisat = this->service.rapoarte();
	for ( auto each : deAfisat)
		cout << "Gen : " << each.getGen() << ", nr exemplare : " << each.getContor() << std::endl;
}


void UI::start()
{
	int cmd = 1;
	while (cmd != 0) {
		cout << "1. Adaugare\n2. Afisarea tuturor cartilor\n3. Stergerea unei carti\n4. Modificarea unei carti\n5. Filtrare dupa titlu\n6. Filtrare dupa an\n7. Sortare dupa titlu\n8. Sortare dupa autor\n9. Sortare dupa anul aparitiei & gen\n10. Rapoarte dupa gen\n0. Iesire\n\nComanda : ";
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaCarte();
				cout << "Cartea a fost adaugata cu succes !\n";
				cout << std::endl;
				break;
			case 2:
				if (service.getAll().size() == 0)
					cout << "Nu exista carti\n";
				else
					tipareste(service.getAll());
				cout << std::endl;
				break;
			case 3:
				stergeCarte();
				cout << "Cartea a fost stearsa cu succes !\n";
				cout << std::endl;
				break;
			case 4:
				schimbaCarte();
				cout << "Cartea a fost modificata cu succes !\n";
				cout << std::endl;
				break;
			case 5:
				filtrareTitlu();
				break;
			case 6:
				filtrareAn();
				break;
			case 7:
				tipareste(service.sorteazaTitlu());
				break;
			case 8:
				tipareste(service.sorteazaAutor());
				break;
			case 9:
				tipareste(service.sorteazaGenAn());
				break;
			case 10:
				rapoarte();
				break;
			case 0:
				return;
			}
		}
		catch (ValidationException& ex) {
			cout << ex << std::endl;
		}
		catch (RepoException& repoex) {
			cout << repoex << std::endl;
		}
	}
}

#include "UI.h"
#include <iostream>
#include <functional>
#include "ServiceException.h"
#include "RepoException.h"
#include <algorithm>
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
	cout << "Cartea a fost adaugata cu succes !\n\n";
}

void UI::tipareste(const vector<Carte>& carti)
{
	cout << std::endl;
	for (const auto& c : carti)
		cout << c.getTitlu() << " " << c.getAutor() << " " << c.getGen() << " " << c.getAn() << "\n";
	cout << "\n\n";
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
	cout << "Cartea a fost stearsa cu succes !\n\n";
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
	cout << "Cartea a fost modificata cu succes !\n\n";
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

void UI::golesteCos()
{
	service.golesteCos();
	cout << "\nCosul a fost golit!\n\n";
}

void UI::adaugaCos()
{
	string titlu;
	cout << "Introduceti titlul cartii de adaugat in cos : ";
	cin >> titlu;
	service.adaugaCos(titlu);
	cout << "A fost adaugata in cos!\n";
}

void UI::vizualizeazaCos()
{
	if (service.getCos().size() == 0)
		throw ServiceException("\nCosul este gol!\n");
	tipareste(service.getCos());
}

void UI::genereazaCos() {
	if (service.getAll().size() != 0) {
		string raspuns;
		if (service.getCos().size() != 0) {
			cout << "Cosul dumneavoastra nu este gol, la generare acele carti se vor pierde. Doriti sa generati oricum? (da/nu) : ";
			cin >> raspuns;
			if (raspuns != "da")
				return;
		}
		int nrCarti;
		cout << "Cate carti doriti sa se adauge in cos? ";
		cin >> nrCarti;
		if (nrCarti > 0) {
			service.genereazaCos(nrCarti);
			cout << "\nS-a generat cu succes!\n\n";
		}
		else cout << "\nNumar invalid!\n";
	}
	else cout << "\nNu exista nicio carte inca deci nu se poate genera un cos\n\n";
}

void UI::rapoarte()
{
	if (service.getAll().size() > 0) {
		int m;
		vector<DTO> v = service.medie(m);
		cout << "Reparititia cartilor pe ani : \n";
		for (DTO& obj : v)
		{
			cout << "An: " << obj.getAn() << " Numar de carti: " << obj.getNr() << std::endl;
		}
		cout << "Media anilor pentru cartile din lista este: " << m << '\n\n';
	}
	else {
		cout << "\nNu exista nicio carte in lista! Nu se pot face rapoarte!\n\n";
	}
}

void UI::undo()
{
	service.undo();
	cout << "S-a efectuat undo cu succes!\n\n";
}

void UI::exporta()
{
	string tip;
	string nume;
	cout << "In ce format doriti sa exportati obiectele din cos? \n(HTML/CSV)  : ";
	cin >> tip;
	std::transform(tip.begin(), tip.end(), tip.begin(), ::toupper);
	if (tip == "CSV") {
		cout << "Introduceti numele fisierului :";
		cin >> nume;
		service.exportaCosCSV(nume);
	}
	else {
		if (tip == "HTML") {
			cout << "Introduceti numele fisierului :";
			cin >> nume;
			service.exportaCosHTML(nume);
		}
	}
}


void UI::start()
{
	int cmd = 1;
	while (cmd != 0) {
		cout << "1. Adaugare\n2. Afisarea tuturor cartilor\n3. Stergerea unei carti\n4. Modificarea unei carti\n5. Filtrare dupa titlu\n6. Filtrare dupa an\n7. Sortare dupa titlu\n8. Sortare dupa autor\n9. Sortare dupa anul aparitiei & gen\n10. Goleste cos\n11. Adauga in cos\n12. Vizualizeaza cos\n13. Genereaza cos\n14. Statistica\n15. Undo\n16. Exporta cos\n0. Iesire\n\nComanda : ";
		cin >> cmd;
		try {
			switch (cmd) {
			case 1:
				adaugaCarte();
				break;
			case 2:
				if (service.getAll().size() == 0)
					cout << "\nNu exista carti\n\n";
				else
					tipareste(service.getAll());
				break;
			case 3:
				stergeCarte();
				break;
			case 4:
				schimbaCarte();
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
				golesteCos();
				break;
			case 11:
				adaugaCos();
				break;
			case 12:
				vizualizeazaCos();
				break;
			case 13:
				genereazaCos();
				break;
			case 14:
				rapoarte();
				break;
			case 15:
				undo();
				break;
			case 16:
				exporta();
				break;
			case 0:
				return;
			}
		}
		catch (ValidationException& ex) {
			cout << ex << std::endl << '\n';
		}
		catch (RepoException& repoex) {
			cout << repoex << std::endl << '\n';
		}
		catch (ServiceException& servex) {
			cout << servex << std::endl << '\n';
		}
	}
}

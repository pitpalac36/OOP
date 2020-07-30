#include "Carte.h"
#include "Repository.h"
#include "Validator.h"
#include "Service.h"
#include "UI.h"
#include <iostream>
using std::cout;

void testAll() {
	testCarte();
	testRepo();
	testValidator();
	testService();
	testSortari();
	testFiltrari();
}

int main() {
	testAll();

	Repository repo;
	CarteValidator val;
	Service serv{ repo,val };
	UI ui{ serv };
	ui.start();

	return 0;
}
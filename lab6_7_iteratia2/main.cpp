#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Carte.h"
#include "Repository.h"
#include "Validator.h"
#include "Service.h"
#include "UI.h"

using std::cout;

void testAll() {
	testCarte();
	testRepo();
	testValidator();
	testService();
	testSortari();
	testFiltrari();
	testRapoarte();
}

int main() {

	{
		testAll();
		
		Repository repo;
		CarteValidator val;
		Service serv{ repo,val };
		UI ui{ serv };
		ui.start();
		
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
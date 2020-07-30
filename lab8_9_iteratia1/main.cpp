#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Carte.h"
#include "Repo.h"
#include "Validator.h"
#include "Service.h"
#include "UI.h"


void testAll() {
	testCarte();
	testValidator();
	testRepo();
	testService();
	testSortari();
	testFiltrari();
	testCos();
	testRaport();
}


int main() {
	{
		testAll();
		/*
		Repo repo;
		CarteValidator val;
		Service serv{ repo,val };
		UI ui{ serv };
		ui.start();
		*/
		
		
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
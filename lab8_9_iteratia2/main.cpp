#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include "Carte.h"
#include "Repo.h"
#include "Validator.h"
#include "Service.h"
#include "UI.h"
#include "FileRepo.h"
#include "ChaosMonkeyRepo.h"


void testAll() {
	testCarte();
	testValidator();
	testRepo();
	testService();
	testSortari();
	testFiltrari();
	testUndo();
	testRaport();
	testFileRepo();
	testCos();
	testExport();
	testChaosMonkeyRepo();
}


int main() {
	{
		testAll();
		////FileRepo repo{"file.txt"};
		////Repo repo{};
		//ChaosMonkeyRepo repo{0.5};
		//CarteValidator val{};
		//Cos cos{};
		//Service serv{ repo,val,cos };
		//UI ui{ serv };
		//ui.start();
	}
	_CrtDumpMemoryLeaks();
	return 0;
}
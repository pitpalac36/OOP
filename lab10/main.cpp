#include <QtWidgets/QApplication>
#include "GUI.h"
#include "FileRepo.h"
#include "Validator.h"
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

int main(int argc, char *argv[])
{
	testAll();
	FileRepo repo{ "test\\carti.txt" };
	Cos cos{};
	CarteValidator val;
	Service serv{ repo, val, cos };

	QApplication a(argc, argv);
	GUI gui{serv};
	gui.show();
	return a.exec();
}

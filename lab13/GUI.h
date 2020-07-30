#pragma once
#include <QtWidgets/qwidget.h>
#include <QHBoxLayout>
#include <qradiobutton.h>
#include <qpushbutton.h>
#include "Service.h"
#include <QtWidgets\qtableview.h>
#include <qtablewidget.h>
#include <qlayout.h>
#include <QtWidgets>
#include "ServiceException.h"
#include "RepoException.h"
#include "Validator.h"
#include <QtWidgets\qheaderview.h>
#include "CosGUI.h"
#include "RaportGUI.h"


class GUI : public QWidget
{
public:
	GUI(Service& service) :serv{ service } {
		initGUI();
		loadData(serv.getAll());
		initConnect();
	}
private:
	Service& serv;
	QTableWidget* lista = new QTableWidget{ 100,4 };
	QPushButton* adauga = new QPushButton{ "&ADAUGA" };
	QPushButton* sterge = new QPushButton{ "&STERGE" };
	QPushButton* modifica = new QPushButton{ "&MODIFICA" };
	QPushButton* clear = new QPushButton{ "&CLEAR" };
	QPushButton* cos = new QPushButton{ "&MERGI LA COS..." };
	QPushButton* undo = new QPushButton{ "UNDO" };
	QPushButton* raport = new QPushButton{ "GENEREAZA RAPORT" };
	QLineEdit* titlu = new QLineEdit;
	QLineEdit* autor = new QLineEdit;
	QLineEdit* gen = new QLineEdit;
	QLineEdit* an = new QLineEdit;
	QFormLayout* pereche = new QFormLayout;
	QRadioButton* radioTitlu = new QRadioButton("Titlu", this);
	QRadioButton* radioAutor = new QRadioButton("Autor", this);
	QRadioButton* radioGenAn = new QRadioButton("Anul aparitiei si Gen", this);
	QPushButton* filtrareTitlu = new QPushButton{"FILTRARE DUPA TITLU"};
	QPushButton* filtrareAn = new QPushButton{ "FILTRARE DUPA AN" };
	QVBoxLayout* dynamicLayout = new QVBoxLayout;
	


	void initGUI();

	void loadData(vector<Carte>& sursa);

	void setButoane();

	void clearFields();

	void reloadList();

	void initConnect();

};
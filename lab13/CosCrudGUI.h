#pragma once
#include <QtWidgets/qwidget.h>
#include "Service.h"
#include "ObserverPattern.h"
#include <qlistwidget.h>
#include <qpushbutton.h>
#include <qformlayout.h>
#include <qlineedit.h>
#include <qmessagebox.h>
#include "ServiceException.h"


class CosCrudGUI : public QWidget, public Observer
{
private:
	Service& serv;
	QListWidget* lista = new QListWidget;
	QPushButton* goleste = new QPushButton{ "GOLESTE" };
	QPushButton* genereaza = new QPushButton{ "GENEREAZA" };
	QLineEdit* line = new QLineEdit;


	void update() override {
		loadData();
	}

	void initGUI() {
		auto main = new QVBoxLayout;
		main->addWidget(lista);
		main->addWidget(goleste);
		QFormLayout* pereche = new QFormLayout;
		pereche->addRow(line, genereaza);
		main->addLayout(pereche);
		setLayout(main);
		setMinimumHeight(300);
		setMinimumWidth(400);
	}

	void loadData() {
		lista->clear();
		for (auto& each : serv.getCos())
			lista->addItem(QString::fromStdString(each.toString()));
	}

	void initConnect() {

		QObject::connect(goleste, &QPushButton::clicked, [&]() {
			try {
				serv.golesteCos();
				loadData();
				QMessageBox::information(this, "information", QString::fromStdString("Cosul a fost golit!"));
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}

		});

		QObject::connect(genereaza, &QPushButton::clicked, [&]() {
			int x = line->text().toInt();
			if (x == 0)   // prinde si cazurile de string nenumeric
				QMessageBox::warning(this, "warning", QString::fromStdString("Introduceti un nr natural > 0 !"));
			else {
				serv.genereazaCos(line->text().toInt());
				loadData();
				QMessageBox::information(this, "information", QString::fromStdString("S-a generat cu succes!"));
			}
		});


	}


public:
	CosCrudGUI(Service& s) : serv{s}{
		serv.addObserver(this);
		initGUI();
		loadData();
		initConnect();
	}

	~CosCrudGUI() {
		serv.removeObserver(this);
	}

};
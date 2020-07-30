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

	void initGUI() {
		setButoane();
		setMinimumSize(1000, 500);
		setMaximumSize(1300, 700);
		QStringList labels;
		labels << "Titlu" << "Autor" << "Gen" << "Anul aparitiei";
		lista->setMinimumHeight(200);
		lista->setMinimumWidth(500);
		lista->setSelectionBehavior(QAbstractItemView::SelectRows);   // se selecteaza intreaga coloana
		//lista->setSelectionMode(QAbstractItemView::SingleSelection);   // se selecteaza maxim o coloana
		QHeaderView* header = lista->horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Stretch);

		lista->setHorizontalHeaderLabels(labels);
		QHBoxLayout* mainLayout = new QHBoxLayout;	// main layout
		setLayout(mainLayout);
		QVBoxLayout* leftLayout = new QVBoxLayout;	// left layout (table + radio buttons layout)
		leftLayout->addWidget(lista);
		leftLayout->addWidget(new QLabel{ "Sorteaza dupa:" });
		QHBoxLayout* sortStuff = new QHBoxLayout;	// radio buttons layout
		sortStuff->addWidget(radioTitlu);
		sortStuff->addWidget(radioAutor);
		sortStuff->addWidget(radioGenAn);
		leftLayout->addLayout(sortStuff);
		mainLayout->addLayout(leftLayout);
		QVBoxLayout* rightLayout = new QVBoxLayout;  // main right layout
		pereche->addRow("Titlu ", titlu);
		pereche->addRow("Autor ", autor);
		pereche->addRow("Gen ", gen);
		pereche->addRow("An aparitie  ", an);
		rightLayout->addItem(pereche);
		QHBoxLayout* buttonsLayout = new QHBoxLayout;   // layout pt adauga, sterge, modifica buttons
		QVBoxLayout* vbuttonsLayout = new QVBoxLayout;  // layout pt clear, undo, cos buttons
		vbuttonsLayout->setAlignment(Qt::AlignCenter);
		vbuttonsLayout->addWidget(clear);
		vbuttonsLayout->addWidget(undo);
		vbuttonsLayout->addWidget(cos);
		vbuttonsLayout->addWidget(raport);
		rightLayout->addItem(vbuttonsLayout);
		buttonsLayout->addWidget(adauga);
		buttonsLayout->addWidget(sterge);
		buttonsLayout->addWidget(modifica);
		buttonsLayout->setAlignment(Qt::AlignTop);
		QHBoxLayout* filterLayout = new QHBoxLayout;  // layout pt filter buttons
		filterLayout->addWidget(filtrareTitlu);
		filterLayout->addWidget(filtrareAn);
		rightLayout->addLayout(filterLayout);
		rightLayout->addItem(buttonsLayout);
		rightLayout->addLayout(dynamicLayout);
		mainLayout->addLayout(rightLayout);
	}

	void loadData(vector<Carte>& sursa) {
		QLayoutItem* child;
		while ((child = dynamicLayout->takeAt(0)) != 0)
		{
			if (child->widget() != NULL)
			{
				delete (child->widget());
			}
			delete child;
		}

		int i = 0;
		for (auto& each : sursa) {
			QTableWidgetItem* titlu = new QTableWidgetItem(QString::fromStdString(each.getTitlu()));
			lista->setItem(i, 0, titlu);
			QTableWidgetItem* autor = new QTableWidgetItem(QString::fromStdString(each.getAutor()));
			lista->setItem(i, 1, autor);
			QTableWidgetItem* gen = new QTableWidgetItem(QString::fromStdString(each.getGen()));
			lista->setItem(i, 2, gen);
			QTableWidgetItem* an = new QTableWidgetItem(QString::fromStdString(std::to_string(each.getAn())));
			lista->setItem(i, 3, an);
			i++;

			auto* dynamicButton = new QPushButton{ QString::fromStdString(each.getTitlu()) };
			dynamicLayout->addWidget(dynamicButton);
		}
	}

	void setButoane() {
		adauga->setMaximumWidth(150);
		sterge->setMaximumWidth(150);
		modifica->setMaximumWidth(150);
		undo->setMaximumWidth(200);
		clear->setMaximumWidth(200);
		cos->setMinimumWidth(200);
		raport->setMinimumWidth(200);
	}

	void clearFields() {
		titlu->setText("");
		autor->setText("");
		gen->setText("");
		an->setText("");
		loadData(serv.getAll());	// dupa filtrare (se va afisa lista initiala)
	}

	void reloadList() {
		lista->clearContents();
		loadData(serv.getAll());
		clearFields();
	}

	void initConnect() {

		QObject::connect(clear, &QPushButton::clicked, this, &GUI::clearFields);


		QObject::connect(adauga, &QPushButton::clicked, [&]() {
			try {
				serv.addCarte(titlu->text().toStdString(), autor->text().toStdString(), gen->text().toStdString(), an->text().toInt());
				reloadList();
				QMessageBox::information(this, "information", QString::fromStdString("S-a adaugat cu succes!"));
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this,"warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}
			catch (ValidationException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessages()[0]));
			}

		});


		QObject::connect(modifica, &QPushButton::clicked, [&]() {
			try {
				serv.schimbaCarte(titlu->text().toStdString(), autor->text().toStdString(), gen->text().toStdString(), an->text().toInt());
				reloadList();
				QMessageBox::information(this, "information", QString::fromStdString("S-a modificat cu succes!"));
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}
			catch (ValidationException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessages()[0]));
			}

		});


		QObject::connect(undo, &QPushButton::clicked, [&]() {
			try {
				serv.undo();
				reloadList();
				QMessageBox::information(this, "information", QString::fromStdString("S-a facut undo cu succes!"));
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}
		});


		QObject::connect(lista, &QTableWidget::itemSelectionChanged, [&]() {
			if (lista->selectedItems().isEmpty()) {
				clearFields();
				return;
			}
			QTableWidgetItem* row = lista->selectedItems().at(0);
			QString title = row->text();
			row = lista->selectedItems().at(1);
			QString author = row->text();
			row = lista->selectedItems().at(2);
			QString genre = row->text();
			row = lista->selectedItems().at(3);
			QString year = row->text();
			titlu->setText(title);
			autor->setText(author);
			gen->setText(genre);
			an->setText(year);
		});


		QObject::connect(cos, &QPushButton::clicked, [&]() {
			try {
				qDebug("cos creat\n");
				CosGUI* cosGUI = new CosGUI{ serv };
				cosGUI->show();
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}
			catch (ValidationException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessages()[0]));
			}
		});

		QObject::connect(radioAutor, &QRadioButton::clicked, [&]() {
			loadData(serv.sorteazaAutor());
		});

		QObject::connect(radioTitlu, &QRadioButton::clicked, [&]() {
			loadData(serv.sorteazaTitlu());
		});

		QObject::connect(radioGenAn, &QRadioButton::clicked, [&]() {
			loadData(serv.sorteazaGenAn());
		});

		QObject::connect(raport, &QPushButton::clicked, [&]() {
			RaportGUI* raportGUI = new RaportGUI{ serv };
			raportGUI->show();
		});

		QObject::connect(filtrareTitlu, &QPushButton::clicked, [&]() {
			if(titlu->text().isEmpty())
				QMessageBox::warning(this, "warning", QString::fromStdString("Dati mai intai o limita superioara!"));
			else {
				lista->clearContents();
				loadData(serv.filtreazaTitlu(titlu->text().toStdString()));
			}
		});

		QObject::connect(filtrareAn, &QPushButton::clicked, [&]() {
			if (an->text().isEmpty())
				QMessageBox::warning(this, "warning", QString::fromStdString("Dati mai intai o limita superioara!"));
			else {
				lista->clearContents();
				loadData(serv.filtreazaAn(an->text().toInt()));
			}
		});
		

		QObject::connect(sterge, &QPushButton::clicked, [&]() {
			try {
				QList<QTableWidgetItem*> selected = lista->selectedItems();
				std::vector<bool> removed(lista->rowCount(), false);
				if (selected.size() > 0) {
					for (const auto& each : selected) {
						int row = each->row();
						if (!removed.at(row)) {
							string title = lista->item(row, 0)->text().toStdString();
							string author = lista->item(row, 1)->text().toStdString();
							string genre = lista->item(row, 2)->text().toStdString();
							int year = lista->item(row, 3)->text().toInt();
							serv.stergeCarte(title, author, genre, year);
							removed.at(row) = true;
						}
					}
					reloadList();
					QMessageBox::information(this, "information", QString::fromStdString("S-a sters cu succes!"));
				}
				
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}
			catch (RepoException& ex) {
				QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessage()));
			}
			catch (ValidationException& ex) {
				QMessageBox::warning(this, "warning!", QString::fromStdString(ex.getMessages()[0]));
			}

		});

		}
};
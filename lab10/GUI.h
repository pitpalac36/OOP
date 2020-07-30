#pragma once
#include <QtWidgets/qwidget.h>
#include <QHBoxLayout>
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

class GUI : public QWidget
{
public:
	GUI(Service& service) :serv{ service } {
		initGUI();
		loadData();
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
	QLineEdit* titlu = new QLineEdit;
	QLineEdit* autor = new QLineEdit;
	QLineEdit* gen = new QLineEdit;
	QLineEdit* an = new QLineEdit;
	QFormLayout* pereche = new QFormLayout;

	void initGUI() {
		setMinimumSize(1000, 350);
		QStringList labels;
		labels << "Titlu" << "Autor" << "Gen" << "Anul aparitiei";

		lista->setSelectionBehavior(QAbstractItemView::SelectRows);   // se selecteaza intreaga coloana
		//lista->setSelectionMode(QAbstractItemView::SingleSelection);   // se selecteaza maxim o coloana
		QHeaderView* header = lista->horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Stretch);

		lista->setHorizontalHeaderLabels(labels);
		QHBoxLayout* mainLayout = new QHBoxLayout;
		setLayout(mainLayout);
		mainLayout->addWidget(lista);
		QVBoxLayout* rightLayout = new QVBoxLayout;
		pereche->addRow("Titlu", titlu);
		pereche->addRow("Autor", autor);
		pereche->addRow("Gen", gen);
		pereche->addRow("Anul aparitiei", an);
		rightLayout->addItem(pereche);
		QHBoxLayout* buttonsLayout = new QHBoxLayout;
		QVBoxLayout* vbuttonsLayout = new QVBoxLayout;
		vbuttonsLayout->addWidget(clear);
		vbuttonsLayout->addWidget(cos);
		vbuttonsLayout->addWidget(undo);
		rightLayout->addItem(vbuttonsLayout);
		buttonsLayout->addWidget(adauga);
		buttonsLayout->addWidget(sterge);
		buttonsLayout->addWidget(modifica);
		rightLayout->addItem(buttonsLayout);
		mainLayout->addLayout(rightLayout);
	}

	void loadData() {
		int i = 0;
		for (auto& each : serv.getAll()) {
			QTableWidgetItem* titlu = new QTableWidgetItem(QString::fromStdString(each.getTitlu()));
			lista->setItem(i, 0, titlu);
			QTableWidgetItem* autor = new QTableWidgetItem(QString::fromStdString(each.getAutor()));
			lista->setItem(i, 1, autor);
			QTableWidgetItem* gen = new QTableWidgetItem(QString::fromStdString(each.getGen()));
			lista->setItem(i, 2, gen);
			QTableWidgetItem* an = new QTableWidgetItem(QString::fromStdString(std::to_string(each.getAn())));
			lista->setItem(i, 3, an);
			i++;
		}
	}

	void clearFields() {
		titlu->setText("");
		autor->setText("");
		gen->setText("");
		an->setText("");
	}

	void reloadList() {
		lista->clearContents();
		loadData();
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
#pragma once
#include "Service.h"
#include <QtWidgets/qwidget.h>
#include <qheaderview.h>
#include <QHBoxLayout>
#include <qstackedlayout.h>
#include <qpushbutton.h>
#include <qtablewidget.h>
#include <qcombobox.h>
#include <qmessagebox.h>
#include <qslider.h>
#include <qlabel.h>
#include <qlineedit.h>
#include "ServiceException.h"
#include <qradiobutton.h>
#include "ObserverPattern.h"
#include "CosReadOnlyGUI.h"
#include "CosCrudGUI.h"


class CosGUI : public QWidget, public Observer
{
	Q_OBJECT
private:
	Service& serv;
	QTableWidget* cos = new QTableWidget{ 100,4 };
	QPushButton* adauga = new QPushButton{ "&ADAUGA" };
	QPushButton* goleste = new QPushButton{ "&GOLESTE" };
	QSlider* slider = new QSlider;
	QPushButton* genereaza = new QPushButton{ "&GENEREAZA" };
	QComboBox* all = new QComboBox;
	QLabel* labelSlider = new QLabel;	// indica nr curent din slider
	QLineEdit* filename = new QLineEdit;
	QLabel* labelExport = new QLabel{ "Exporta cosul in fisierul :" };
	QRadioButton* radioCSV = new QRadioButton("CSV", this);
	QRadioButton* radioHTML = new QRadioButton("HTML", this);
	QPushButton* exporta = new QPushButton{ "&EXPORTA" };
	QPushButton* cosCRUD = new QPushButton{ "COS CRUD" };
	QPushButton* cosReadOnly = new QPushButton{ "COS READ-ONLY" };

public:
	CosGUI(Service& s) : serv{s}{
		serv.addObserver(this);
		initGUI();
		loadData();
		initConnect();
	}

	void update() override {
		reloadList();
	}

	void initGUI() {

		setMinimumSize(700, 500);
		
		slider->setTickPosition(QSlider::TicksRight);   // valorile pt slider - pe partea dreapta
		slider->setMinimum(1);
		slider->setMaximum(100);
		cos->setSelectionBehavior(QAbstractItemView::SelectRows);   // se selecteaza intreaga coloana
		cos->setSelectionMode(QAbstractItemView::SingleSelection);   // se selecteaza maxim o coloana
		QStringList labels;
		labels << "Titlu" << "Autor" << "Gen" << "Anul aparitiei";
		QHeaderView* header = cos->horizontalHeader();
		QVBoxLayout* mainLayout = new QVBoxLayout;	// main layout : va contine main horizontal layout si export layout

		cosCRUD->setMaximumWidth(150);
		cosReadOnly->setMaximumWidth(150);
		mainLayout->addWidget(cosCRUD);		// cos new stuff
		mainLayout->addWidget(cosReadOnly);

		header->setSectionResizeMode(QHeaderView::Stretch);
		cos->setHorizontalHeaderLabels(labels);
		QHBoxLayout* mainHorizontalLayout = new QHBoxLayout;	// main horizontal layout
		setLayout(mainLayout);
		QGridLayout* rightLayout = new QGridLayout;   // layout pt : adauga, goleste, genereaza
		QHBoxLayout* comboboxButtonPair = new QHBoxLayout;
		QHBoxLayout* emptyLayout = new QHBoxLayout;
		emptyLayout->addWidget(goleste);
		comboboxButtonPair->addWidget(all);
		comboboxButtonPair->addWidget(adauga);
		QHBoxLayout* sliderButtonPair = new QHBoxLayout;
		sliderButtonPair->addWidget(labelSlider);
		sliderButtonPair->addWidget(slider);
		sliderButtonPair->addWidget(genereaza);
		rightLayout->addItem(comboboxButtonPair,0,1);
		rightLayout->addItem(sliderButtonPair,1,1);
		rightLayout->addItem(emptyLayout,2,1);
		mainHorizontalLayout->addWidget(cos);
		QHBoxLayout* exportLayout = new QHBoxLayout;	// layout pt exportarea cosului
		exportLayout->addWidget(labelExport);
		exportLayout->addWidget(filename);
		exportLayout->addWidget(radioCSV);
		exportLayout->addWidget(radioHTML);
		exportLayout->addWidget(exporta);
		mainHorizontalLayout->addLayout(rightLayout);
		mainLayout->addLayout(mainHorizontalLayout);
		mainLayout->addLayout(exportLayout);
	}

	void reloadList() {
		cos->clearContents();
		int i = 0;
		for (auto& each : serv.getCos()) {
			QTableWidgetItem* titlu = new QTableWidgetItem(QString::fromStdString(each.getTitlu()));
			cos->setItem(i, 0, titlu);
			QTableWidgetItem* autor = new QTableWidgetItem(QString::fromStdString(each.getAutor()));
			cos->setItem(i, 1, autor);
			QTableWidgetItem* gen = new QTableWidgetItem(QString::fromStdString(each.getGen()));
			cos->setItem(i, 2, gen);
			QTableWidgetItem* an = new QTableWidgetItem(QString::fromStdString(std::to_string(each.getAn())));
			cos->setItem(i, 3, an);
			i++;
		}
	}

	void loadData() {
		reloadList();
		for (auto& each : serv.getAll())
			all->addItem(QString::fromStdString(each.getTitlu()));
	}

	void initConnect() {

		QObject::connect(slider, &QSlider::valueChanged, this, [=]() {
			labelSlider->setText(QString::number(slider->value()));
		});

		QObject::connect(adauga, &QPushButton::clicked, [&]() {
			try {
				serv.adaugaCos(all->currentText().toStdString());
				reloadList();
				QMessageBox::information(this, "information", QString::fromStdString("S-a adaugat cu succes!"));
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}

		});

		QObject::connect(genereaza, &QPushButton::clicked, [&]() {
			try {
				int dimensiune = slider->value();
				serv.genereazaCos(dimensiune);
				reloadList();
				QMessageBox::information(this, "information", QString::fromStdString("S-a generat cu succes!"));
				slider->setSliderPosition(1);
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}

		});

		QObject::connect(goleste, &QPushButton::clicked, [&]() {
			try {
				serv.golesteCos();
				reloadList();
				QMessageBox::information(this, "information", QString::fromStdString("Cosul a fost golit!"));
			}
			catch (ServiceException& ex) {
				QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
			}

		});

		QObject::connect(cosCRUD, &QPushButton::clicked, [&]() {
			CosCrudGUI* crud = new CosCrudGUI{ serv };
			crud->show();
		});

		QObject::connect(cosReadOnly, &QPushButton::clicked, [&]() {
			CosReadOnlyGUI* ro = new CosReadOnlyGUI{ serv };
			ro->show();
		});


		QObject::connect(exporta, &QPushButton::clicked, [&]() {
			if (radioCSV->isChecked()) {
				try {
					if (valid(filename)) {
						serv.exportaCosCSV(filename->text().toStdString());
						filename->setText("");
						radioCSV->setChecked(false);
						QMessageBox::information(this, "information", QString::fromStdString("S-a exportat cu succes!"));
					}
					else
						QMessageBox::warning(this, "warning", QString::fromStdString("Introduceti mai intai numele fisierului CSV!"));
				}
				catch (ServiceException& ex) {
					QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
				}
			}
			else {
				if (radioHTML->isChecked()) {
					try {
						if (valid(filename)) {
							serv.exportaCosHTML(filename->text().toStdString());
							filename->setText("");
							radioHTML->setChecked(false);
							QMessageBox::information(this, "information", QString::fromStdString("S-a exportat cu succes!"));
						}
						else
							QMessageBox::warning(this, "warning", QString::fromStdString("Introduceti mai intai numele fisierului HTML!"));
					}
					catch (ServiceException& ex) {
						QMessageBox::warning(this, "warning", QString::fromStdString(ex.getMessage()));
					}
				}
				else
					QMessageBox::warning(this, "warning", QString::fromStdString("Selectati mai intai o extensie de fisier!"));
			}

		});

	}


	bool valid(QLineEdit* fisier) {
		string nume = fisier->text().toStdString();
		if (nume.size() == 0)
			return false;
		if (std::count(nume.begin(), nume.end(), ' ') > 0)
			return false;
		return true;
	}

	~CosGUI() {
		serv.removeObserver(this);
	}
};
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
#include "ServiceException.h"

class CosGUI : public QWidget
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

public:
	CosGUI(Service& s) : serv{s}{
		initGUI();
		loadData();
		initConnect();
	}

	void initGUI() {
		setMinimumSize(700, 300);
		
		slider->setTickPosition(QSlider::TicksRight);   // valorile pt slider - pe partea dreapta
		slider->setMinimum(1);
		slider->setMaximum(100);
		cos->setSelectionBehavior(QAbstractItemView::SelectRows);   // se selecteaza intreaga coloana
		cos->setSelectionMode(QAbstractItemView::SingleSelection);   // se selecteaza maxim o coloana
		QStringList labels;
		labels << "Titlu" << "Autor" << "Gen" << "Anul aparitiei";
		QHeaderView* header = cos->horizontalHeader();
		header->setSectionResizeMode(QHeaderView::Stretch);
		cos->setHorizontalHeaderLabels(labels);
		QHBoxLayout* mainLayout = new QHBoxLayout;
		setLayout(mainLayout);
		QGridLayout* rightLayout = new QGridLayout;   // qvboxlayout
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
		mainLayout->addWidget(cos);
		mainLayout->addLayout(rightLayout);
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

	}
};
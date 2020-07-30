#pragma once
#include "Service.h"
#include <qlabel.h>
#include <qboxlayout.h>
#include "ObserverPattern.h"

class RaportGUI : public QWidget, public Observer
{
private:
	int m;
	Service& serv;
	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* info1 = new QLabel{ "Repartitia cartilor pe ani este :" };
	QLabel* info2 = new QLabel{ "Media anilor de aparitie este :" };
	QLabel* labelut = new QLabel{""};
	QPushButton* ok = new QPushButton{"OK"};

public:
	RaportGUI(Service& serv) : serv{ serv } {
		setMinimumSize(300, 200);
		setLayout(layout);
		layout->addWidget(info1);
		showRaport();
		labelut->setText({ QString::number(m) });
		layout->addWidget(info2);
		layout->addWidget(labelut);
		ok->setMaximumWidth(100);
		layout->addWidget(ok);
		initConnect();
	}

	void update() override {
		clearLayout(layout);
		layout = new QVBoxLayout;
		setLayout(layout);
		layout->addWidget(info1);
		showRaport();
		labelut->setText({ QString::number(m) });
		layout->addWidget(info2);
		layout->addWidget(labelut);
		ok->setMaximumWidth(100);
		layout->addWidget(ok);
	}

	void showRaport() {
		vector<DTO>& rap = serv.medie(m);
		for (auto& each : rap) {
			layout->addWidget(new QLabel{ "anul :" + QString::number(each.getAn()) + "    numar carti :" + QString::number(each.getNr())});
		}
	}

	void clearLayout(QLayout* layout) {
		QLayoutItem* child;
		while ((child = layout->takeAt(0)) != 0)
		{
			child->widget()->setParent(NULL);
			layout->removeItem(child);
			delete child;
		}
		delete layout;
	}

	void initConnect() {
		QObject::connect(ok, &QPushButton::clicked, [&]() {
			close();
		});
	}
};
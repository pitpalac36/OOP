#pragma once
#include "Service.h"
#include <qlabel.h>
#include <qboxlayout.h>

class RaportGUI : public QWidget
{
private:
	Service& serv;
	QVBoxLayout* layout = new QVBoxLayout;
	QLabel* info1 = new QLabel{ "Repartitia cartilor pe ani este :" };
	QLabel* info2 = new QLabel{ "Media anilor de aparitie este :" };
	QPushButton* ok = new QPushButton{"OK"};

public:
	RaportGUI(Service& serv) : serv{ serv } {
		setMinimumSize(300, 200);
		setLayout(layout);
		layout->addWidget(info1);
		int m = 0;
		showRaport(m);
		layout->addWidget(info2);
		layout->addWidget(new QLabel{ QString::number(m) });
		ok->setMaximumWidth(100);
		layout->addWidget(ok);
		initConnect();
	}

	void showRaport(int &deReturnat) {
		int m = 0;
		vector<DTO> rap = serv.medie(m);
		for (auto& each : rap) {
			layout->addWidget(new QLabel{ "anul :" + QString::number(each.getAn()) + "    numar carti :" + QString::number(each.getNr())});
		}
		deReturnat = m;
	}

	void initConnect() {
		QObject::connect(ok, &QPushButton::clicked, [&]() {
			close();
		});
	}
};


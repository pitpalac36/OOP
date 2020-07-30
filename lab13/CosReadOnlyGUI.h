#pragma once
#include <QtWidgets/qwidget.h>
#include "ObserverPattern.h"
#include "Service.h"
#include <QPainter>
#include <qboxlayout.h>


class CosReadOnlyGUI : public QWidget, public Observer
{

private:
	Service& serv;

	void update() override{
		repaint();
	}

	void initGUI() {
		QHBoxLayout* main = new QHBoxLayout;
		setLayout(main);
		setMinimumHeight(300);
		setMinimumWidth(400);
	}

	void paintEvent(QPaintEvent* ev) override{
		QPainter p{ this };
		int i = 10;
		for (const auto& each : serv.getCos()) {
			p.drawRect(i, 0, 20, 30);
			i += 40;
		}
	}

public:

	CosReadOnlyGUI(Service& s) : serv{ s } {
		serv.addObserver(this);
		initGUI();
	}

	~CosReadOnlyGUI() {
		serv.removeObserver(this);
	}
	
};
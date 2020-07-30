#pragma once
#include "Repo.h"
#include "Service.h"
#include "Cos.h"

class ActiuneUndo
{
public:
	virtual void doUndo() = 0;

	/*
	  destructor virtual pentru a ne asigura ca la delete se apeleaza destructorul din clasa care trebuie
	*/
	virtual ~ActiuneUndo() = default;
};


class UndoAdauga : public ActiuneUndo {
private:
	AbstractRepo& r;
	Carte adaugata;
public:
	UndoAdauga(AbstractRepo& repo, const Carte& carte) : r{ repo }, adaugata{ carte }{}

	void doUndo() override {
		r.sterge(adaugata);
	}

};

class UndoSterge : public ActiuneUndo {
private:
	AbstractRepo& r;
	Carte stearsa;
public:
	UndoSterge(AbstractRepo& repo, const Carte& carte) : r{ repo }, stearsa{ carte }{}

	void doUndo() override {
		r.adauga(stearsa);
	}

};


class UndoModifica : public ActiuneUndo {
private:
	AbstractRepo& r;
	Carte veche;
public:
	UndoModifica(AbstractRepo& repo, const Carte& carte) : r{ repo }, veche{carte}{}

	void doUndo() override {
		r.modifica(veche.getTitlu(), veche.getAutor(), veche.getGen(), veche.getAn());
	}

};



class UndoAdaugareCos : public ActiuneUndo {
private:
	Cos& cos;
	Carte adaugata;
public:
	UndoAdaugareCos(Cos& c, const Carte& book) : cos{ c }, adaugata{ book }{}
	

	void doUndo() override {
		cos.stergeCos(adaugata.getTitlu());
	}

};
#pragma once
using namespace std;

template<typename T>
struct Nod {
	T valoare;
	Nod* urm;
	Nod(T val) : valoare{ val }, urm{ nullptr }{}
	Nod(T val, Nod* urmator) : valoare{ val }, urm{ urmator }{}
};

//forward declaration
template <typename T>
class ListIterator;

template <typename T>
class List
{
private:
	Nod<T>* prim;

	// dealocarea spatiului ocupat de nodurile listei
	void dealocaNoduri();

	/*
	Face o copie a listei inlantuite
	Parcurge recursiv lista si creaza noduri in care copieaza valorile
	*/
	Nod<T>* copiazaLista(Nod<T>* curent);

public:
	// constructor fara parametri
	List() : prim{ nullptr } {}

	// constructor de copiere (Rule of three)
	List(const List& other);

	// operator de asignare (Rule of three)
	void operator=(const List& other);

	// destructor (Rule of three)
	~List();

	// returneaza numarul de elemente
	size_t size() const;


	// adauga un element la inceputul listei
	void add_front(T elem);

	// adauga un element la finalul listei
	void push_back(T elem);

	void erase(T elem);

	// primul element din lista
	T& first() const;

	/*
	Returneaza un iterator pozitionat pe primul element
	*/
	ListIterator<T> begin() const;

	/*
	Returneaza un iterator cu nodul nullptr (dupa ultimul element)
	*/
	ListIterator<T> end() const;

	/*
	Returneaza elementul de pe pozitia data ca parametru
	*/
	T& operator[](size_t poz);

};



template<typename T>
inline void List<T>::dealocaNoduri()
{
	auto nCurent = prim;
	while (nCurent != nullptr) {
		auto aux = nCurent->urm;
		delete nCurent;
		nCurent = aux;
	}
	prim = nullptr;
}

template<typename T>
inline Nod<T>* List<T>::copiazaLista(Nod<T>* curent)
{
	if (curent == nullptr)
		return nullptr;
	auto n = new Nod<T>{ curent->valoare };
	n->urm = copiazaLista(curent->urm);
	return n;
}

template<typename T>
inline List<T>::List(const List& other)
{
	prim = copiazaLista(other.prim);
}

template<typename T>
inline void List<T>::operator=(const List& other)
{
	dealocaNoduri();
	prim = copiazaLista(other.prim);
}

template<typename T>
inline List<T>::~List()
{
	dealocaNoduri();
}

template<typename T>
inline size_t List<T>::size() const
{
	auto nCurent = prim;
	int lg = 0;
	while (nCurent != nullptr) {
		lg++;
		nCurent = nCurent->urm;
	}
	return lg;
}

template<typename T>
inline void List<T>::add_front(T elem)
{
	Nod<T>* n = new Nod<T>{ elem, prim };
	prim = n;
}

template<typename T>
inline void List<T>::push_back(T elem)
{
	auto nCurent = prim;
	while (nCurent != nullptr && nCurent->urm != nullptr)
		nCurent = nCurent->urm;
	if (nCurent == nullptr)
		prim = new Nod<T>{ elem,nullptr };
	else
		nCurent->urm = new Nod<T>{ elem,nullptr };
}

template<typename T>
inline void List<T>::erase(T elem)
{
	auto nCurent = prim;
	if (nCurent->valoare == elem) // se sterge primul element
	{
		auto aux = prim->urm;
		delete prim;
		prim = aux;
	}
	else {
		auto nUrm = prim->urm;
		while (nCurent->urm != nullptr) {
			if (nUrm->valoare == elem) {
				nCurent->urm = nUrm->urm;
				delete nUrm;
				return;
			}
			nCurent = nCurent->urm;
			nUrm = nUrm->urm;
		}
	}
}

template<typename T>
inline T& List<T>::first() const
{
	return prim->valoare;
}

template<typename T>
T& List<T>::operator[](size_t poz)
{
	auto nCurent = prim;
	size_t lg = 0;
	while (lg < poz) {
		lg++;
		nCurent = nCurent->urm;
	}
	return nCurent->valoare;
}



template <typename T>
class ListIterator {
private:
	Nod<T>* curent;
public:
	ListIterator(Nod<T>* c) : curent{ c } {}

	// necesar pt range for
	bool operator!=(const ListIterator& other);

	/*
	trece la urmatorul element din interatie (pt range for)
	*/
	void operator++();

	/*
	Returneaza elementul curent din interatie (pt range for)
	*/
	T& operator*();
};




template<typename T>
inline ListIterator<T> List<T>::begin() const
{
	return ListIterator<T>{prim};
}

template<typename T>
inline ListIterator<T> List<T>::end() const
{
	return ListIterator<T>{nullptr};
}


template<typename T>
inline bool ListIterator<T>::operator!=(const ListIterator& other)
{
	return curent != other.curent;
}

template<typename T>
inline void ListIterator<T>::operator++()
{
	curent = curent->urm;
}

template<typename T>
inline T& ListIterator<T>::operator*()
{
	return curent->valoare;
}

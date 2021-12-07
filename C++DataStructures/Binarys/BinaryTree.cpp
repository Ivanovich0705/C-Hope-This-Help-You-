#include "pch.h"
#include <iostream>
using namespace std;
using namespace System;

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
	Nodo(T elemento) {
		this->elemento = elemento;
		izq = der = nullptr;

	}
	Nodo() {}
};

template <class T>
class ArbolB {
	Nodo<T>* raiz;

private:
	bool _insertar(Nodo<T>*& nodo, T e) {
		if (nodo == nullptr) {
			nodo = new Nodo<T>(e);
		}
		else if (e < nodo->elemento) {
			return _insertar(nodo->izq, e);
		}
		else if (e >= nodo->elemento) {
			return _insertar(nodo->der, e);
		}
	}
	void _enOrden(Nodo<T>* nodo) {
		if (nodo == nullptr) return;
		_enOrden(nodo->izq);
		cout << nodo->elemento << " ";
		_enOrden(nodo->der);
	}

	bool _vacio() {
		return raiz == nullptr;
	}
	int _cantidad(Nodo<T>* nodo) {
		if (nodo == nullptr)
			return 0;
		else
		{
			int ci, cd;
			ci = _cantidad(nodo->izq);
			cd = _cantidad(nodo->der);
			return 1 + ci + cd;
		}

	}
public:
	ArbolB() {

		raiz = nullptr;
	}
	bool insertar(T e) {
		return _insertar(raiz, e);
	}
	void enOrden() {
		_enOrden(raiz);
	}
	int cantidad() {
		return _cantidad(raiz);
	}
	int altura() {
		return _altura(raiz);
	}
};

int main()
{
	ArbolB<int> tree;
	for (int i = 0; i < 10; ++i)
		tree.insertar(i);
	tree.enOrden();
	cout << "\n" << tree.cantidad();
	return 0;

}

#pragma once
#include <algorithm>
#include "SHA265.h"

template <class T>
class Nodo {
public:
	T elemento;
	Nodo* izq;
	Nodo* der;
    int h;
	Nodo(T elemento) {
		this->elemento = elemento;
		izq = der = nullptr;
	}
	Nodo() {  }
    static int altura(Nodo<T>* n) {
        return n == nullptr ? -1 : n->h;
    }
    void actualizarAltura() {
        h = max(altura(der), altura(izq));
    }
};

template <class T, class K>
class BinaryT {
    Nodo<T>* raiz;
    function<int(T, T)>comparar;
    function<bool(T, T)>cmp;
    function<K(T)>get;
private:

    bool _insertar(Nodo<T>*& nodo, T e) {
        if (nodo == nullptr) {
            nodo = new Nodo<T>(e);
        }
        else if (cmp(e,nodo->elemento)) {
            return _insertar(nodo->izq, e);
        }
        else if (!cmp(e,nodo->elemento)) {
            return _insertar(nodo->der, e);
        }
        balancear(nodo);
    }

    void _enOrden(Nodo<T>* nodo) {
        if (nodo == nullptr) return;
        _enOrden(nodo->izq);
        cout << get(nodo->elemento) << endl;
        _enOrden(nodo->der);
    }

    bool _vacio() {
        return raiz == nullptr;
    }

    int _cantidad(Nodo<T>* nodo) {
        if (nodo == nullptr)
            return 0;
        else {

            int ci, cd;
            ci = _cantidad(nodo->izq);
            cd = _cantidad(nodo->der);
            return 1 + ci + cd;
        }

    }

    T _minimo(Nodo<T>* nodo) {
        if (nodo->izq == nullptr)
            return nodo->elemento;
        else
            return _minimo(nodo->izq);
    }

    long _altura(Nodo<T>* nodo) {
        long izq = 0, der = 0;
        if (nodo == nullptr)
            return -1;
        else {

            izq = 1 + _altura(nodo->izq);
            der = 1 + _altura(nodo->der);
            return max(izq, der);
        }
    }

     bool _eliminar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr)
            return false;
        else {
            int r = comparar(nodo->elemento, e);
            if (r < 0) {
                return _eliminar(nodo->der, e);
            }
            else if (r > 0) {
                return _eliminar(nodo->izq, e);
            }
            else { // r==0 encontró el elemento e en el arbol
                if (nodo->der == nullptr & nodo->izq == nullptr) {
                    nodo = nullptr;
                    delete nodo;
                    return true;
                }
                else if (nodo->izq == nullptr) {
                    nodo = nodo->der;
                    return true;
                }
                else if (nodo->der == nullptr) {
                    nodo = nodo->izq;
                    return true;
                }
                else {
                    //_minimo(nodo->der);
                    Nodo<T>* aux = nodo->der; //buscara el menor elemento por la derecha
                    while (aux->izq != nullptr) {

                        aux = aux->izq; //Se obtiene la hoja menor
                    }
                    //nodo->elemento = _minimo(nodo->der); //Se actualiza el elemento en el nodo raiz y
                    nodo->elemento = aux->elemento; //Se actualiza el elemento en el nodo raiz y
                    return _eliminar(nodo->der, aux->elemento); //se envía a eliminar el elemento en el arbol por la derecha
                    //return _eliminar(nodo->der, _minimo(nodo->der)); //se envía a eliminar el elemento en el arbol por la derecha
                }
            }
        }
    }

    T _buscar(Nodo<T>* nodo, T e) {
        if (nodo == nullptr)
            return nullptr;
        else {
            int r = comparar(nodo->elemento, e);
            if (r == 0) {
                return nodo->elemento;
            }
            else if (r < 0) {
                return _buscar(nodo->der, e);
            }
            else
                return _buscar(nodo->izq, e);

        }
    }


    T& _obtener(Nodo<T>* nodo, T e) {//Complejidad algoritimica: O(log_2(n))
        if (nodo == nullptr)                    //  1 + max(INTERNA IF, INTERNA ELSE) ----> 4 + 2(log_2(n))
            return nodo->elemento;          //----> 1
        else {                              // ----------> 3 + 2(log_2(n))
            int r = comparar(nodo->elemento, e);// 1 + 2(log_2(n))
            if (r == 0) return nodo->elemento;  // 1 +  max(INTERNA IF, INTERNA ELSE) ---> 2 + log_2(n)
            else if (r < 0)                     // 1 + max(INTERNA IF, INTERNA ELSE)  ---> 1 + log_2(n)
                return _obtener(nodo->der, e);  // log_2(n)
            else
                return _obtener(nodo->izq, e);  // log_2(n)
        }
    }

    void rotarDerecha(Nodo<T>*& nodo) {
        Nodo<T>* p = nodo->izq;
        nodo->izq = p->der;
        nodo->actualizarAltura();
        p->der = nodo;
        nodo = p;
        nodo->actualizarAltura();
    }
    void rotarIzquierda(Nodo<T>*& nodo) {
        Nodo<T>* p = nodo->der;
        nodo->der = p->izq;
        nodo->actualizarAltura();
        p->izq = nodo;
        nodo = p;
        nodo->actualizarAltura();
    }

    void balancear(Nodo<T>*& nodo) {
        int dif = Nodo<T>::altura(nodo->izq) - Nodo<T>::altura(nodo->der);
        if (dif > 1) {
            int hdi = Nodo<T>::altura(nodo->der->izq);
            int hdd = Nodo<T>::altura(nodo->der->der);
            if (hdi > hdd) {
                rotarDerecha(nodo->der);
            }
            rotarIzquierda(nodo);
        }
        if (dif < -1) {
            int hii = Nodo<T>::altura(nodo->izq->izq);
            int hid = Nodo<T>::altura(nodo->izq->der);
            if (hii < hid) {
                rotarIzquierda(nodo->izq);
            }
            rotarDerecha(nodo);
        }
    }

public:

    BinaryT(){}
    BinaryT(function<int(T, T)>comparar, function<K(T)>get, function<bool(T,T)>cmp) {
        this->get = get;
        this->cmp = cmp;
        this->comparar = comparar;
        raiz = nullptr;

    }
    void setCompare(function<int(T, T)>comparar) {

        this->comparar = comparar;
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

    T minimo() {
        return _minimo(raiz);
    }

    long altura() {
        return _altura(raiz);
    }
    T buscar(T e) {
        return _buscar(raiz, e);
    }
    bool modify(T e) {
        return _modify(raiz, e);
    }
    bool eliminar(T e) {
        _eliminar(raiz, e);
    }

    T& obtener(T e) {
        return _obtener(raiz, e);
    }
};

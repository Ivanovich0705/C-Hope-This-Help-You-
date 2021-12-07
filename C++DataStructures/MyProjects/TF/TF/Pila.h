#pragma once
#include "Entidades.h"

template <typename T>
class Nod {
public:
    T elemento;
    Nod<T>* siguiente;
    Nod<T>* anterior;
    Nod(T e) { elemento = e; siguiente = anterior = nullptr; }
};

template <typename T>
class Pila {
public:
    Nod<T>* inicio;
    Nod<T>* fin;
    long cantidad = 0;
public:
    Pila() {
        inicio = fin = nullptr;
        cantidad = 0;
    }
    
    void push(T e) {//O(1)
        Nod<T>* nuevo = new Nod<T>(e);
        if (inicio == nullptr) {
            inicio = fin = nuevo;
        }
        else {
            nuevo->anterior = fin;
            fin->siguiente = nuevo;
            fin = nuevo;
        }
        inicio = nuevo;
        ++cantidad;
    }

    void top(function<void(T)>funFront) {
        funFront(fin->elemento);

    }

    void pop() {
        if (cantidad == 0)
            return;
        else if (cantidad == 1)
        {
            delete inicio;
            inicio = fin = nullptr;
        }
        else {
            Nod<T>* aux = fin;
            fin = aux->anterior;
            fin->siguiente = nullptr;
            delete aux;
        }
        cantidad--;
    }

    T top() {
        if (inicio != nullptr)
            return fin->elemento;
    }

    int size() {
        short c = 0;
        Nod<T>* aux = inicio;
        while (aux != nullptr) {
            c++;
            aux = aux->siguiente;
        }
        return c;
    }

};

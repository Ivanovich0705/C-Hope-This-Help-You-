#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <functional>
using namespace System;
using namespace std;


template<typename T>
int Apart(T a[], int p, int r, function<bool(T, T)>cmp) {
    T x = a[r];
    int i = p - 1; //indice de los menores
    for (int j = p; j < r; j++) {
        if (cmp(a[j], x)) {
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i + 1], a[r]);
    return i + 1;
}

template<typename T>
void Quicksort(T a[], int p, int r, function<bool(T,T)>cmp) {
    int q; //para almacenar el indice del pivote

    if (p < r) {
        q = Apart<T>(a, p, r, cmp); //devuelve el indice del pivote
        Quicksort(a, p, q - 1, cmp);
        Quicksort(a, q + 1, r, cmp);
    }
}



template<typename T>
void Merge(T*& a1, T*& a2, T*& a, long n, function<bool(T,T)> cmp) {
    long i, j, k;
    i = j = k = 0;
    while (i < n / 2 && j < n - (n / 2)) {
        if (cmp(a1[i], a2[j])) {
            a[k] = a1[i];
            i++; k++;
        }
        else {
            a[k] = a2[j];
            j++; k++;
        }
    }
    while (i < n / 2) {
        a[k] = a1[i];
        i++; k++;
    }
    while (j < n - (n / 2)) {
        a[k] = a2[j];
        j++; k++;
    }
}


template<class T>
void MergeSort(T a[], long n, function<bool(T,T)>cmp) {
    if (n > 1) {
        T* a1 = new T[n / 2];
        T* a2 = new T[n - n / 2];
        for (long i = 0; i < n / 2; i++) {
            a1[i] = a[i];
        }
        for (long i = n / 2; i < n; i++) {
            a2[i - n / 2] = a[i];
        }
        MergeSort(a1, n / 2, cmp);
        MergeSort(a2, n - n / 2, cmp);
        Merge(a1, a2, a, n, cmp);
    }
}


template <typename T>
void show(T a[], long n, function<void(T)>print){

    for (long i = 0; i < n; i++) {

        print(a[i]);

    }

}

int generateYear() {

    return rand() % 31 + 1990;

}

string generateMarca() {
    int choosen;
    choosen = rand() % 5;
    switch (choosen)
    {
    case 0: return "Audi"; break;
    case 1: return "Mazda"; break;
    case 2: return "Mercedez"; break;
    case 3: return "Tesla"; break;
    case 4: return "BMW"; break;
    case 5: return "Porche"; break;
    default:
        break;
    }

}

double generatePrecio() {

    return (double)rand() / (RAND_MAX) + 8000 + (rand() % 2);
}

class Vehiculo {
    string marca;
    int year;
    double precio;
public:
    Vehiculo(string marca, int year, double precio) : marca(marca), year(year), precio(precio) {}

    string getMarca() { return marca; }
    double getPrecio() { return precio; }
    int getYear() { return year; }
    string toString() { return marca + "\t" + to_string(year) + "\t" + to_string(precio); }

};

void Mergaxmple() {
    long cant = 50000;
    Vehiculo* cars[50000];
    for (long i = 0; i < cant; i++) {
        cars[i] = new Vehiculo(generateMarca(), generateYear(), generatePrecio());
    }
    
    clock_t inicio = clock();
    MergeSort<Vehiculo*>(cars, cant, 
        [](Vehiculo* a, Vehiculo* b) {return a->getYear() < b->getYear(); });
    clock_t fin = clock();
    double tiempo = (fin - inicio) / CLOCKS_PER_SEC;
    cout << tiempo;

    //show<Vehiculo*>(cars, cant, [](Vehiculo* a)->void {cout << a->toString() << endl; });

}

void QuickSample() {
    long cant = 10000;
    Vehiculo* cars[10000];
    for (long i = 0; i < cant; i++) {
        cars[i] = new Vehiculo(generateMarca(), generateYear(), generatePrecio());
    }

    clock_t inicio = clock();
    Quicksort<Vehiculo*>(cars, 0, cant - 1, 
        [](Vehiculo* a, Vehiculo* b) {return a->getYear() < b->getYear(); });
    clock_t fin = clock();
    double tiempo = (fin - inicio) / CLOCKS_PER_SEC;
    cout << tiempo;
    show<Vehiculo*>(cars, cant, [](Vehiculo* a)->void {cout << a->toString() << endl; });
}

int main()
{
    srand(time(0));
    //Mergaxmple();
    QuickSample();
    return 0;
}

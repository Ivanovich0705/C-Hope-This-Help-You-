#include "pch.h"
#include <iostream>
#include <conio.h>
#include <functional>
using namespace System;
using namespace std;

template<typename T>
void Merge(T*& a1, T*& a2, T*& a, long n) {
    long i, j, k;
    i = j = k = 0;
    while (i < n / 2 && j < n - (n / 2)) {
        if (a1[i] < a2[j]) {
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


template<typename T>
void MergeSort(T*& a, long n) {
    if (n > 1) {
        T* a1 = new T[n / 2];
        T* a2 = new T[n - n / 2];
        for (long i = 0; i < n / 2; i++) {
            a1[i] = a[i];
        }
        for (long i = n / 2; i < n; i++) {
            a2[i - n / 2] = a[i];
        }
        MergeSort(a1, n / 2);
        MergeSort(a2, n - n / 2);
        Merge(a1, a2, a, n);
    }
}

template <typename T>
void generate(T*& a, long n) {

    for (long i = 0; i < n; i++) {

        a[i] = rand() % 200 + 1;

    }

}

template <typename T>
void show(T* a, long n) {

    for (long i = 0; i < n; i++) {

        cout << a[i] << endl;

    }

}

void example() {
    long cant = 10000000;
    long* a = new long[cant];
    generate(a, cant);
    clock_t inicio = clock();
    MergeSort(a, cant);
    clock_t fin = clock();
    double tiempo = (fin - inicio) / CLOCKS_PER_SEC;
    cout << tiempo;
    //show(a, cant);

}


int main()
{
    srand(time(0));
    example();
    return 0;
}
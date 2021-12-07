#include "pch.h"
#include <iostream>
#include <string>
#include <conio.h>
#include <functional>
#include <algorithm>
using namespace System;
using namespace std;

template<typename T>
void heapify(T arr[], int n, int i, function<bool(T,T)>cmp){

	int largest = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	
	if (l < n && cmp(arr[l],arr[largest])) {

		//cout << "And largest ";
		largest = l;
	}

	if (r < n && cmp(arr[r],arr[largest]))
		largest = r;


	if (largest != i) {

		swap(arr[i], arr[largest]);
		heapify(arr, n, largest, cmp);
	}
}

template<typename T>
void heapSort(T arr[], int nn, function<bool(T,T)> cmp){

	for (int i = nn / 2 - 1; i >= 0; i--)
		heapify(arr, nn, i, cmp);


	for (int i = nn - 1; i > 0; i--) {

		swap(arr[0], arr[i]);

		heapify(arr, i, 0, cmp);

	}
}

template<typename T>
void printArray(T arr[], int n, function<void(T)> print){

	for (int i = 0; i < n; ++i) {
		print(arr[i]);
	}
	
}

class Candidato {

	string nombre;
	float patrimonio;
	short edad;

public:
	Candidato(string nombre = "", float patrimonio = 50000, short edad = 40) {
		this->nombre = nombre;
		this->patrimonio = patrimonio;
		this->edad = edad;

	}

	bool operator<(Candidato& c) {

		if (this->nombre.compare(c.nombre) < 0) {
			return true;
		}

		else return false;
	}

	bool operator>(Candidato& c) {

		if (this->edad > c.edad) {

			return true;
		}
		else return false;
	}

	friend ostream& operator<<(ostream& os, Candidato& c) {
		
		os << c.nombre << " " << c.edad << " " << c.patrimonio << endl;
		return os;
	}

	string toString() {
		return nombre + "\t" + to_string(edad) + "\t" + to_string(patrimonio);
	}

	string getNombre() { return nombre; }
	int getEdad() { return edad; }
	double getPatrimonio() { return patrimonio; }
};


int generateEdad() {

	return rand() % 45;

}

string generateNombre() {
	int choosen;
	choosen = rand() % 5;
	switch (choosen)
	{
	case 0: return "Ivan"; break;
	case 1: return "Matias"; break;
	case 2: return "Diego"; break;
	case 3: return "Vargas"; break;
	case 4: return "Josselyn"; break;
	case 5: return "Fabricio"; break;
	default:
		break;
	}

}

double generatePatrimonio() {

	return (double)rand() / (RAND_MAX)+8000 + (rand() % 2);
}

int main()
{
	Candidato* candidates[50000];
	for (long i = 0; i < 50000; i++) {
		candidates[i] = new Candidato(generateNombre(), generatePatrimonio(), generateEdad());
	}
	
	heapSort<Candidato*>(candidates, 50000, [](Candidato* a, Candidato* b)->bool {return a->getEdad() > b->getEdad(); });
	printArray<Candidato*>(candidates, 50000, [](Candidato* a) {cout << a->toString() << endl; });

    return 0;
}

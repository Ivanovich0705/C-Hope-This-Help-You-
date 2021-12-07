#pragma once
#include "Lista.h"
#include "Pila.h"
#include "Entidad.h"

class Alumno :public Entidad{

public:
	Pila<string> commments;

	Alumno(string nombre, string sede, string codigo, string edad)  {
		setCodigo(codigo);
		setNombre(nombre);
		setEdad(edad);
		setSede(sede);
	}
	Alumno(){}

	int getSizeComments() { return this->commments.cantidad; }

	void addComment(string com) {
		commments.push(com);
	}

	void showComments() {
		
		while (commments.inicio != nullptr && commments.cantidad != 0) {
			commments.top([](string v) {cout << v << endl; });
			commments.pop();
			cout << "Presiona para mostrar siguiente comentario: "<<endl;
			system("pause");
		}
	}
	
	

};

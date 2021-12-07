#pragma once
#include "Entidad.h"

class Personaje :public Entidad {
	bool conquistado = false;
public:
	Personaje(){
		
		x = rand() % 1150;
		y = rand() % 739;

		dx = rand() % 8 - 3;
		dy = rand() % 8 - 3;

		ancho = 135.2;
		alto = 131.5;

		IDx = 0;

		srand(time(NULL));
		IDy = rand() % 6;
	}
	bool GetConquistado() {

		return conquistado;
	}
	void SetConquistado(bool value) {

		conquistado = value;
	}
	void Mover(Graphics^ g) override {

		if (!(x + dx >= 0 && x + ancho + dx < 1150))
			dx *= -1;
		x += dx;

		if (!(y + dy >= 0 && y + alto + dy < 739))
			dy *= -1;
		y += dy;
	}
	void Mostrar(Graphics^ g, Bitmap^ img) override {

		Rectangle corte = Rectangle(IDy * alto, IDx * ancho, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);
		g->DrawRectangle(Pens::Purple, Hitbox());
			IDx = (IDx + 1) % 5;
	}

};

class Personajes {

private:
	vector<Personaje*> personajes;
public:
	int Marron = 0;
	int Celeste = 0;
	int Rojo = 0;
	int Azul = 0;
	int Gris = 0;
	int Rosa = 0;
public:

	~Personajes(){

		for each (Personaje * P in personajes)
			delete P;
	}

	int Size(){

		return personajes.size();
	}

	void DoRanking() {
		for (int i = 0; i < Size(); i++) {
			if (personajes[i]->GetConquistado() == true) {
				switch (personajes[i]->GetIDY())
				{
				case 0:Celeste++; break;
				case 1:Rojo++; break;
				case 2:Azul++; break;
				case 3:Marron++; break;
				case 4:Gris++; break;
				case 5:Rosa++; break;
				}
			}
		}
	}
	Personaje* Get(int pos){

		return personajes[pos];
	}

	void Agregar(Personaje* personaje){

		personajes.push_back(personaje);
	}

	void Conquista() {
		for (int i = 0; i < Size(); i++) {
			for (int j = i + 1; j < Size(); j++) {
				Personaje* E1 = Get(i);
				Personaje* E2 = Get(j);
				if (E1->Hitbox().IntersectsWith(E2->Hitbox()) && E1->GetConquistado() == false && E2->GetConquistado() == false) {
					E2->SetConquistado(true);
					E2->SetAnchoD(E2->GetAnchoD() - 20);
					E2->SetAltoD(E2->GetAltoD() - 20);
					E2->SetIDY(E1->GetIDY());
				}
			}
		}
	}

	void Mover(Graphics^ g){

		for each (Personaje * P in personajes)
			P->Mover(g);
	}

	void Mostrar(Graphics^ g, Bitmap^ img){

		for each (Personaje * P in personajes)
			P->Mostrar(g, img);
	}
};

#pragma once
#include "Personaje.h"

ref class Juego //Clase Controladora
{
private:
	Personajes* personajes;

	Bitmap^ imgAmong;
	Bitmap^ imgMapa;

	int coolDown;
	short N;
	int cont = 0;

public:
	bool TimeOver = false;
	Juego()
	{
		Random x;
		N = x.Next(6, 13);

		imgAmong = gcnew Bitmap("Resources/sprite.png");
		imgMapa=gcnew Bitmap("Resources/mapa.png");

		personajes = new Personajes();

	}
	~Juego()
	{
		delete personajes;
	}


	void Mover(Graphics^ g){

		if (clock() - coolDown >= 2500 && cont <= N) {//2000 es el tiempo leido x ejemplo
			
			personajes->Agregar(new Personaje);

			coolDown = clock();

			cont++;
			
		}
		if (clock() >= 35000)//el tiempo que se desea del juego
		{
			TimeOver = true;
		}
		personajes->Conquista();
		personajes->Mover(g);

	}
	void MostrarRanking(Graphics^ g) {
		personajes->DoRanking();
		g->DrawString("Ranking:", gcnew Font("Arial", 30), Brushes::Red, 100, 300);
		g->DrawString("Color Marron: " + (personajes->Marron), gcnew Font("Arial", 30), Brushes::Black, 100, 340);
		g->DrawString("Color Rojo: " + (personajes->Rojo), gcnew Font("Arial", 30), Brushes::Black, 100, 380);
		g->DrawString("Color Celeste: " + (personajes->Celeste), gcnew Font("Arial", 30), Brushes::Black, 100, 420);
		g->DrawString("Color Rosa: " + (personajes->Rosa), gcnew Font("Arial", 30), Brushes::Black, 100, 450);
		g->DrawString("Color Gris: " + (personajes->Gris), gcnew Font("Arial", 30), Brushes::Black, 100, 490);
		g->DrawString("Color Azul: " + (personajes->Azul), gcnew Font("Arial", 30), Brushes::Black, 100, 530);
	}
	void Mostrar(Graphics^ g){
		g->DrawImage(imgMapa, Rectangle(0, 0, 986, 989));
		personajes->Mostrar(g, imgAmong);

	}
};
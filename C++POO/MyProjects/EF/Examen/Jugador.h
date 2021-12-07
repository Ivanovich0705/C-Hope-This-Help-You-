#pragma once
#include "Entidad.h"

enum SpriteJugador
{
	CaminarArriba = 0,
	CaminarIzquierda = 1,
	CaminarAbajo = 2,
	CaminarDerecha = 3
};

class Jugador: public Entidad {

	SpriteJugador accion;
public:
	Jugador(Bitmap^ img) {

		x = 50; y = 70;
		dx = dy = 0;
		ancho = img->Width / 9;
		alto = img->Height / 8;

		accion = CaminarAbajo;
	}

	void SetAccion(SpriteJugador value) {

		if (accion != value)
			IDx = 0;

		accion = value;
	}

	void Mover(Graphics^ g) {

		if (x + dx >= 0 && x + ancho + dx < g->VisibleClipBounds.Width)
			x += dx;
		if (y + dy >= 0 && y + alto + dy < g->VisibleClipBounds.Height)
			y += dy;
	}
	void Mostrar(Graphics^ g, Bitmap^ img) {

		Rectangle corte = Rectangle(IDx * ancho, accion * alto, ancho, alto);
		g->DrawImage(img, Area(), corte, GraphicsUnit::Pixel);

		if (dx != 0 || dy != 0)
			IDx = (IDx + 1) % 8;
	}
};
#pragma once
#include <iostream>
#include <fstream>
#include <time.h>
#include <vector>
using namespace std;
using namespace System;
using namespace System::Drawing;
using namespace System::Windows::Forms;

class Entidad
{
protected:
	int x, y;
	int dx, dy;
	int ancho, alto;

	int IDy;
	int IDx;

	int anchoD = 90.13;
	int altoD = 87.6;
	

public:
	Entidad() {

		x = 0;
		y = 0;

		dx = 0;
		dy = 0;

		IDy = 0;
		IDx = 0;
	}

	int GetX() {

		return x;
	}
	int GetY() {

		return y;
	}
	int GetDX() {

		return dx;
	}
	int GetDY() {

		return dy;
	}
	int GetIDX() {

		return IDx;
	}
	int GetIDY() {

		return IDy;
	}
	int GetAnchoD() {

		return anchoD;
	}
	int GetAltoD() {

		return altoD;
	}
	void SetX(int value) {

		x = value;
	}
	void SetY(int value) {

		y = value;
	}
	void SetAnchoD(int value) {

		anchoD = value;
	}
	void SetAltoD(int value) {

		altoD = value;
	}
	void SetDX(int value) {

		dx = value;
	}
	void SetDY(int value) {

		dy = value;
	}

	void SetIDX(int value) {

		IDx = value;
	}
	void SetIDY(int value) {

		IDy = value;
	}

	Rectangle Area() {

		return Rectangle(x, y, anchoD, altoD);
	}

	Rectangle Hitbox() {
		
		return Rectangle(x + 20, y + 20, ancho / 3, alto / 3);
	}
	virtual void Mover(Graphics^ g) {

		x += dx;
		y += dy;
	}

	virtual void Mostrar(Graphics^ g, Bitmap^ img) {

		g->FillRectangle(Brushes::Blue, Area());
	}
};
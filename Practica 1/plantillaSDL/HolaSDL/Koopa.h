#ifndef KOOPA_H
#define KOOPA_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

class Game;

using uint = unsigned int;
using namespace std;

class Koopa
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	// MOVIMIENTO
	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento

public:
	Koopa();

	// -- render --
	void render() const;

	// -- update --
	void update();

	// -- hit --
	// controla las colisiones
	//	-> Si el koopa es golpeado desde arriba por el player: se muere
	//	-> Otra colision: muere player
	// (en futuras versiones al ser golpeado se hara caparazon y podra lanzar)
	void hit(SDL_Rect* rect);
};

#endif
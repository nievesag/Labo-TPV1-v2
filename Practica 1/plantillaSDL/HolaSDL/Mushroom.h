#ifndef MUSHROOM_H
#define MUSHROOM_H

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

class Mushroom
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	// MOVIMIENTO
	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento

public:
	Mushroom();

	// -- render --
	void render() const;

	// -- update --
	void update();

	// -- hit --
	// controla las colisiones
	//	-> Se mueve hacia la derecha en el mapa, cambiando de dir cuando choca con un obstaculo
	//	-> Si Mario colisiona con Mushroom se convierte en SuperMario
	void hit(SDL_Rect* rect);
};

#endif
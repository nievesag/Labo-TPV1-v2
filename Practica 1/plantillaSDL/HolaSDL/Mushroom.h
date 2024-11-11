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
#include "Collision.h"

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

	SDL_Rect destRect;

	bool alive;

public:
	Mushroom(Game* g, Point2D<double> p);

	// -- render --
	void render() const;

	// -- update --
	void update();

	void updateRect();

	void moveSeta();

	// -- hit --
	// controla las colisiones
	//	-> Se mueve hacia la derecha en el mapa, cambiando de dir cuando choca con un obstaculo
	//	-> Si Mario colisiona con Mushroom se convierte en SuperMario
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void killSeta() { alive = false; }

	bool getAlive() {
		return alive;
	}
};

#endif
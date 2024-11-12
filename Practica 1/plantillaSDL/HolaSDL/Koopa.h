#ifndef KOOPA_H
#define KOOPA_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "Collision.h"

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

	int koopaFrame;

	bool frozen; // para llevar control de objetos inactivos
	bool alive;

	bool grounded;

	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

	SDL_Rect destRect;

public:
	Koopa(Game* g, std::istream& in);

	// -- render --
	void render() const;

	// -- update --
	void update();

	void updateRect();

	// -- hit --
	// controla las colisiones
	//	-> Si el koopa es golpeado desde arriba por el player: se muere
	//	-> Otra colision: muere player
	// (en futuras versiones al ser golpeado se hara caparazon y podra lanzar)
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	void killKoopa() { alive = false; }

	bool getAlive() {
		return alive;
	}

private:
	void moveKoopa();
};

#endif
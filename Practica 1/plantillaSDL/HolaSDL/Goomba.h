#ifndef GOOMBA_H
#define GOOMBA_H

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

class Goomba
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	// MOVIMIENTO
	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento

	int goombaFrame;

	bool frozen; // para llevar control de objetos inactivos
	bool alive;

	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

public:
	Goomba(Game* g, std::istream& in);

	// -- render --
	void render() const;

	// -- update --
	void update();

	// -- hit --
	// controla las colisiones
	//	-> Si el goomba es golpeado desde arriba por el player: se muere
	//	-> Otra colision: 
	//		-> si supermario: vuelve a mario
	//		-> si mario: quita vida
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

private:
	void moveGoomba();
};

#endif
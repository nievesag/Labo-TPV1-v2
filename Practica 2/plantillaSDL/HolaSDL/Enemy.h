#ifndef ENEMY_H
#define ENEMY_H

#include "SceneObject.h"

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

class Enemy : public SceneObject
{
private:

	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	// MOVIMIENTO
	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento

	int enemyFrame;

	bool frozen; // para llevar control de objetos inactivos
	bool alive;

	bool grounded;

	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

	SDL_Rect destRect;

public:
	Enemy(Game* g, std::istream& in);

	// -- render --
	virtual void render() const override;

	// -- update --
	virtual void update();

	virtual void updateRect();

	// -- hit --
	// controla las colisiones
	//	-> Si el enemigo es golpeado desde arriba por el player: se muere
	//	-> Otra colision: 
	//		-> si supermario: vuelve a mario
	//		-> si mario: quita vida
	virtual Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	void killEnemy() { alive = false; }

	bool getAlive() {
		return alive;
	}
	
	virtual Collision tryToMove(Vector2D<double> v, Collision::Target t) override;

protected:
	virtual void moveEnemy(); 
	virtual void animate();
};

#endif
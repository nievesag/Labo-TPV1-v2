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


	int enemyFrame;

	bool frozen; // para llevar control de objetos inactivos
	bool alive;

	bool grounded;

	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

	int moveDelay = 5;

	SDL_Rect destRect;

public:
	Enemy(Game* g, Point2D<int> position, Texture* t);

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
	
	virtual Collision tryToMove(Vector2D<int>& v, Collision::Target t) override;
	
	virtual void collisionResult();

	virtual void manageCollisions(Collision collision) override;

	SceneObject* clone() const override;

protected:
	virtual void moveEnemy(); 
	virtual void animate();
};

#endif
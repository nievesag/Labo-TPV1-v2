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

	bool frozen; // para llevar control de objetos inactivos
	bool alive;

	bool grounded;
	int moveDelay = 5;

public:
	Enemy(Game* g, Point2D<int> p, Texture* t);


	// -- update --
	virtual void update() override;

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
	
	//virtual Collision tryToMove(Vector2D<int>& v, Collision::Target t) override;
	
	virtual void collisionResult();

	virtual void manageCollisions(Collision c) override;

	SceneObject* clone() const override;
	virtual void updateAnim() override;

protected:
	virtual void moveEnemy(); 
};

#endif
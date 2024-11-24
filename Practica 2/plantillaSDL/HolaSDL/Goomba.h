#ifndef GOOMBA_H
#define GOOMBA_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "Enemy.h"

class Game;

using uint = unsigned int;
using namespace std;

class Goomba : public Enemy
{
private:
	

public:
	Goomba(Game* g, Point2D<int> p, Texture* t);

	// -- update --
	void update() override;
	void updateRect() override;

	virtual void collisionResult() override;

};

#endif
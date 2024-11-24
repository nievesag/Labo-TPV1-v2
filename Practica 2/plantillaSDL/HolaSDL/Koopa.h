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

#include "Enemy.h"

class Game;

using uint = unsigned int;
using namespace std;

class Koopa : public Enemy
{
private:

public:
	Koopa(Game* g, Point2D<int> p, Texture* t);

	// -- update --
	void update();

	virtual void collisionResult() override;

	SceneObject* clone() const override;

	//void updateRect() override;
};

#endif
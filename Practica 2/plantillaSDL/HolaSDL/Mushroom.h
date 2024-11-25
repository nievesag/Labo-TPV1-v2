#ifndef MUSHROOM_H
#define MUSHROOM_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "Collision.h"
#include "Pickable.h"

class Game;

using uint = unsigned int;
using namespace std;

class Mushroom : public Pickable
{
private:
	int moveDelay = 5;

public:
	Mushroom(Game* g, Point2D<int> p, Texture* t);

	void render() override;

	// -- update --
	void update() override;

	void moveSeta();

	void triggerAction() override;

	SceneObject* clone() const override;

	//void updateRect() override;
	void triggerAction() override;
	void updateAnim() override;

	SceneObject* clone() const override;
};

#endif
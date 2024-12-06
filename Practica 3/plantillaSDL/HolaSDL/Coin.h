#ifndef COIN_H
#define COIN_H

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

class Coin : public Pickable
{
public:
	Coin(Game* g, Point2D<int> p, Texture* t, PlayState* play);

	void render() const override;

	// -- update --
	void update() override;

	void triggerAction() override;

	SceneObject* clone() const override;

	void updateAnim() override;
private:
	int coinFrame;
};

#endif
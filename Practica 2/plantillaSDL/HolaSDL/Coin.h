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
	Point2D<int> new_position;	// posicion que tendria si avanza en Point2D
	SDL_Rect new_rect;				// rect que tendria si avanza en Point2D

	bool alive;

public:
	Coin(Game* g, Point2D<int> p, Texture* t);

	void render() override;

	// -- update --
	void update() override;

	void killCoin() { alive = false; }

	bool getAlive() {
		return alive;
	}

	void triggerAction() override;

	SceneObject* clone() const override;

	void updateAnim() override;
private:
	int coinFrame;
};

#endif
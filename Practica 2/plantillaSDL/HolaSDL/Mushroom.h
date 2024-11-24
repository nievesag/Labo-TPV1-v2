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
	//Vector2D<int> direction;	// direccion de movimiento

	Point2D<int> new_position;	// posicion que tendria si avanza en Point2D
	SDL_Rect new_rect;				// rect que tendria si avanza en Point2D

	bool alive;

public:
	Mushroom(Game* g, Point2D<int> p, Texture* t);

	// -- update --
	void update() override;

	void moveSeta();

	void killSeta() { alive = false; }

	bool getAlive() {
		return alive;
	}

	//void updateRect() override;
	void triggerAction() override;
	void updateAnim() override;

	SceneObject* clone() const override;
};

#endif
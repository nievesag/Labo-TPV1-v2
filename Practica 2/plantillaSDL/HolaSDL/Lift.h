#ifndef LIFT_H
#define LIFT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "SceneObject.h"

class Game;

using uint = unsigned int;
using namespace std;

class Lift : public SceneObject
{
private:
	Game* game = nullptr;		// puntero al juego

public:
	Lift(Game* g, Point2D<int> position, Texture* t, Vector2D<double> speed);

	// -- render --
	void render() override;

	// -- update --
	void update() override;

	void updateRect();

	Point2D<int> getPos() const { return position; }

	SceneObject* clone() const override;

	Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	void manageCollisions(Collision collision) override;

private:
	void moveLift();

};

#endif
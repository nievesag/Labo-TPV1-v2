#pragma once

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

class Pickable : public SceneObject
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	SDL_Rect destRect;

	bool alive;

	bool picked = false;

public:

	Pickable(Game* g, Point2D<double> position, Texture* texture);

	virtual void render() const override;
	virtual void update();
	virtual void updateRct();

	virtual Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	bool isPicked() { return picked; }

	void manageCollisions(Collision collision) override;

protected:
	virtual void triggerAction() = 0;
};
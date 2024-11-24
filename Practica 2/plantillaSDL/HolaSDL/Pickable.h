#ifndef PICKABLE_H
#define PICKABLE_H

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
	bool alive;
	bool picked = false;

public:
	Pickable(Game* g, Point2D<int> p, Texture* t);

	virtual void render() override;
	virtual void update();

	virtual Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	bool isPicked() { return picked; }

	void manageCollisions(Collision collision) override;

	//SceneObject* clone() const override;

	void updateAnim() override;

protected:
	virtual void triggerAction() = 0;
};

#endif
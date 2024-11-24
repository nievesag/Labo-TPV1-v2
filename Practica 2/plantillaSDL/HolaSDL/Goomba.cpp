#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, Point2D<int> p, Texture* t)
	: Enemy(g, p, t)
{
	//direction = Vector2D<int>(0, 0);

	//goombaFrame = 0;

	//frozen = true;
	//alive = true;
}


void Goomba::update() {

}

void Goomba::updateRect()
{

}

void Goomba::render()
{

	SceneObject::render();
}

void Goomba::collisionResult()
{
}

void Goomba::updateAnim()
{
	frameTimer++;
	if (frameTimer >= 1200) {
		frameTimer = 0;
		frame = (frame + 1) % 2;
	}
}

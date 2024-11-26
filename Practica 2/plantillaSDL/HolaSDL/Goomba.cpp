#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, Point2D<int> p, Texture* t)
	: Enemy(g, p, t)
{
	frame = 0;
	frameTimer = 0;
}

void Goomba::update()
{
	Enemy::update();
}

SceneObject* Goomba::clone() const
{
	return new Goomba(*this);
}

void Goomba::render()
{
	Enemy::render();
	updateAnim();
}

void Goomba::collisionResult()
{

}

void Goomba::updateAnim()
{
	frameTimer++;
	if (frameTimer >= 3) {
		frameTimer = 0;
		frame = (frame + 1) % 2;
	}
}
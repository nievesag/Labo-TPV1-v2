#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, Point2D<int> p, Texture* t, Vector2D<int> s, PlayState* play)
	: Enemy(g, p, t, s, play)
{
	frame = 0;
	frameTimer = 0;
	flip = SDL_FLIP_NONE;
}

void Goomba::update()
{
	updateRect();
	updateAnim();
	Enemy::update();
}

SceneObject* Goomba::clone() const
{
	return new Goomba(*this);
}

void Goomba::render() const
{
	SceneObject::render();
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
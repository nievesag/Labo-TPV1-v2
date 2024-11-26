#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, Point2D<int> p, Texture* t, Vector2D<int> s)
	: Enemy(g, p, t, s)
{
	frame = 0;
	frameTimer = 0;
	flip = SDL_FLIP_NONE;
}

void Koopa::update()
{
	//Hacer la logica del caparazon
	Enemy::update();
}

void Koopa::collisionResult()
{
	
}

SceneObject* Koopa::clone() const
{
	return new Koopa(*this);
}

void Koopa::render()
{

	Enemy::render();
	updateAnim();
}

void Koopa::updateAnim()
{
	frameTimer++;
	if (frameTimer >= 5) 
	{
		frameTimer = 0;
		frame = (frame + 1) % 2;
	}
}
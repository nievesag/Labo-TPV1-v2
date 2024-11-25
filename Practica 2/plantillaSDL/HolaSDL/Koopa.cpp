#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, Point2D<int> p, Texture* t)
	: Enemy(g, p, t)
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

void Koopa::render()
{

	Enemy::render();
	updateAnim();
}

void Koopa::updateAnim()
{
	frameTimer++;
	if (frameTimer >= 5) {
		frameTimer = 0;
		frame = (frame + 1) % 2;
	}
}

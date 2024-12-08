#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, Point2D<int> p, Texture* t, Vector2D<int> s, PlayState* play)
	: Enemy(g, p, t, s, play)
{
	frame = 0;
	frameTimer = 0;
	flip = SDL_FLIP_NONE;
}

void Koopa::update()
{
	//Hacer la logica del caparazon

	updateRect();
	updateAnim();
	Enemy::update();
}

void Koopa::collisionResult()
{
	
}

SceneObject* Koopa::clone() const
{
	return new Koopa(*this);
}

void Koopa::render() const
{
	Enemy::render();
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

void Koopa::updateRect()
{
	destRect.x = position.getX() - playState->getMapOffset();
	destRect.h = texture->getFrameHeight() * scale;
	destRect.w = texture->getFrameWidth() * scale;
	destRect.y = position.getY() - 32;
}

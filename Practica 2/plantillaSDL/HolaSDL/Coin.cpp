#include "Coin.h"
#include "Game.h"
#include "Collision.h"

Coin::Coin(Game* g, Point2D<int> p, Texture* t)
	: Pickable(g, p, t)
{
	setScale(2);
	frame = 0;
	frameTimer = 0;
	flip = SDL_FLIP_NONE;
}

void Coin::render()
{
	Pickable::render();
	updateAnim();
}

void Coin::update()
{
}



void Coin::triggerAction()
{
	game->givePoints(200);
}

SceneObject* Coin::clone() const
{
	return nullptr;
}

void Coin::updateAnim()
{
	frameTimer++;
	if (frameTimer >= 5)
	{
		frameTimer = 0;
		coinFrame = (coinFrame + 1) % 4;

		if (coinFrame == 0) {
			frame = 0;
		}
		else if (coinFrame == 1) {
			frame = 1;
		}
		else if (coinFrame == 2) {
			frame = 2;
		}
		else if (coinFrame == 3) {
			frame = 3;
		}
	}
}

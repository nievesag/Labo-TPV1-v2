#include "Coin.h"
#include "Game.h"
#include "Collision.h"

Coin::Coin(Game* g, Point2D<int> p, Texture* t)
	: Pickable(g, p, t)
{
	position.setY(position.getY() * 32);
	position.setX(position.getX() * 32);
	position = position - Point2D<int>(0, 1);
	

	alive = true;
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
	return new Coin(*this);
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
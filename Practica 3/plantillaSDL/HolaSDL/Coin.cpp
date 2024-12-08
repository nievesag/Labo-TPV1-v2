#include "Coin.h"
#include "Game.h"
#include "Collision.h"

Coin::Coin(Game* g, Point2D<int> p, Texture* t, PlayState* play)
	: Pickable(g, p, t, play)
{
	scale = 2;
}

void Coin::render() const
{
	Pickable::render();
}

void Coin::update()
{
	updateRect();
	updateAnim();
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

void Coin::updateRect()
{
	destRect.x = position.getX() - playState->getMapOffset();
	destRect.h = texture->getFrameHeight() * scale;
	destRect.w = texture->getFrameWidth() * scale;
	destRect.y = position.getY();
}

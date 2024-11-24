#include "Coin.h"
#include "Game.h"
#include "Collision.h"

Coin::Coin(Game* g, Point2D<int> p, Texture* t)
	: Pickable(g, p, t)
{
	position.setY(position.getY() * 32);
	position.setX(position.getX() * 32);
	position = position - Point2D<int>(0, 1);
	direction = Vector2D<int>(0, 0);

	alive = true;
}

void Coin::update()
{
}

void Coin::updateRect()
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
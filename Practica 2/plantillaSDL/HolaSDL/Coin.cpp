#include "Coin.h"
#include "Game.h"
#include "Collision.h"

Coin::Coin(Game* g, Point2D<double> position, Texture* texture)
	: Pickable(g, position, texture)
{
	game = g;

	position.setY(position.getY() * 32);
	position.setX(position.getX() * 32);
	position = position - Point2D<double>(0, 1);
	direction = Vector2D<int>(0, 0);

	alive = true;
	texture = game->getTexture(Game::COIN);
}

void Coin::update()
{
}

void Coin::triggerAction()
{
	game->givePoints(200);
}
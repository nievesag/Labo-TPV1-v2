#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, Point2D<int> position, Texture* texture)
	: Enemy(g, position, texture)
{
	texture = game->getTexture(Game::KOOPA); // textura inicial

}


void Koopa::update()
{
		//Hacer la logica del caparazon
}

void Koopa::collisionResult()
{
}



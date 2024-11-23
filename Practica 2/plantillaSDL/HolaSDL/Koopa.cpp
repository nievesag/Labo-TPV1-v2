#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, Point2D<double> pos, Texture* texture)
	: Enemy(g, pos, texture)
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



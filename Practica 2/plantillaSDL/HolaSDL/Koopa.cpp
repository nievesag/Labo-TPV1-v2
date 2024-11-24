#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, Point2D<int> p, Texture* t)
	: Enemy(g, p, t)
{

}

void Koopa::update()
{
		//Hacer la logica del caparazon
}

void Koopa::collisionResult()
{
}
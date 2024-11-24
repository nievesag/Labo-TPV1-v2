#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, Point2D<int> position, Texture* t)
	: Enemy(g, position, texture), texture(t)
{
	//in >> position;
	//position = position - Point2D<double>(0, 1); // coloca bien al goomba
	//direction = Vector2D<int>(0, 0);

	//goombaFrame = 0;

	//frozen = true;
	//alive = true;
}


void Goomba::update() {

}

void Goomba::collisionResult()
{
}

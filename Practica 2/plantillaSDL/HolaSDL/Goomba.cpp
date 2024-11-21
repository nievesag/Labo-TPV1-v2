#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, Point2D<int> pos, Texture* t)
	: Enemy(g, pos, texture), texture(t)
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

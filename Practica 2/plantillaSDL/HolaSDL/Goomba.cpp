#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, Point2D<int> pos, Texture* texture)
	: Enemy(g, pos, texture)
{
	//in >> position;
	//position = position - Point2D<double>(0, 1); // coloca bien al goomba
	//direction = Vector2D<int>(0, 0);
	texture = game->getTexture(Game::GOOMBA); // textura inicial de mario

	//goombaFrame = 0;

	//frozen = true;
	//alive = true;
}


void Goomba::update() {

}

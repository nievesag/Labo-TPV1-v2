#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, std::istream& in)
	: Enemy(g, in)
{
	texture = game->getTexture(Game::KOOPA); // textura inicial

}


void Koopa::update()
{
		//Hacer la logica del caparazon
}



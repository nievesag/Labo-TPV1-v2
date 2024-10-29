#include "Goomba.h"
#include "Game.h"

Goomba::Goomba(Game* g, std::istream& in) 
	: game(g)
{
	in >> position;
	position = position - Point2D<double>(0, 1); // coloca bien al goomba
	direction = Vector2D<int>(0, 0);
	texture = game->getTexture(Game::GOOMBA); // textura inicial de mario

	goombaFrame = 0;

	frozen = true;
	alive = true;
}

void Goomba::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (position.getX() * TILE_SIDE) - game->getMapOffset();
	destRect.y = (position.getY() * TILE_SIDE);

	texture->renderFrame(destRect, 0, goombaFrame);
}

void Goomba::update()
{
	// si la pos del goomba es menor que el offset mas el ancho de la pantalla -> se defrozea
	if ((position.getX()*32)-texture->getFrameWidth()*2.8 < (game->getMapOffset() + game->getWinWidth()))
	{
		frozen = false;
	}

	moveGoomba();
}

void Goomba::hit(SDL_Rect* rect)
{

}

void Goomba::moveGoomba()
{
	direction = Vector2D<int>(0, 0);

	if (!frozen) 
	{
		direction = Vector2D<int>(-1, 0);

		position.setX(position.getX() + (direction.getX() * GOOMBA_SPEED * 0.3));
	}

	if (direction.getX() != 0)
	{
		frameTimer++;
		if (frameTimer >= 800) {  // Velocidad del ciclo
			frameTimer = 0;
			animationFrame = (animationFrame + 1) % 2;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (animationFrame == 0) goombaFrame = 1;
			else if (animationFrame == 1) goombaFrame = 0;
		}
	}
}
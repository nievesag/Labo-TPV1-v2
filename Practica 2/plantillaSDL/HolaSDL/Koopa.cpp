#include "Game.h"
#include "Koopa.h"

Koopa::Koopa(Game* g, std::istream& in)
	: game(g)
{
	in >> position;
	position = position - Point2D<double>(0, 1); // lo coloca bien
	direction = Vector2D<int>(0, 0);
	texture = game->getTexture(Game::KOOPA); // textura inicial

	koopaFrame = 0;

	frozen = true;
	alive = true;
}

void Koopa::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (position.getX() * TILE_SIDE) - game->getMapOffset();
	destRect.y = (position.getY() * TILE_SIDE - 1 * TILE_SIDE);

	texture->renderFrame(destRect, 0, koopaFrame);
}

void Koopa::update()
{
	// si la pos del koopa es menor que el offset mas el ancho de la pantalla -> se defrozea
	if ((position.getX() * 32) - texture->getFrameWidth() * 2.8 < (game->getMapOffset() + game->getWinWidth()))
	{
		frozen = false;
	}

	updateRect();
	moveKoopa();
}

void Koopa::updateRect()
{
	destRect.h = texture->getFrameHeight() * 2;
	destRect.w = texture->getFrameWidth() * 2;
	destRect.x = position.getX() * TILE_SIDE;
	destRect.y = position.getY() * TILE_SIDE;
}

Collision Koopa::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;

	// si hay colision
	if (SDL_HasIntersection(&rect, &destRect))
	{
		c.collides = true;

		// si se origina en mario...
		if (fromPlayer)
		{
			// si la colision es por: arr -> muere el koopa
			if ((rect.y + rect.h) <= destRect.y+1) c.damages = false;

			// otra colision -> hiere a mario
			else c.damages = true;
		}
		// si no... con el tilemap
		else
		{
			// choca por la izq -> va a der
			if (destRect.x >= (rect.x + rect.w))
			{
				direction.setX(1);
			}
			// choca por la der -> va a izq
			else if ((destRect.x + destRect.w) <= rect.x)
			{
				direction.setX(-1);
			}
		}
	}

	return c;
}

void Koopa::moveKoopa()
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
			animationFrame = (animationFrame + 1) % 2;

			if (animationFrame == 0) koopaFrame = 1;
			else if (animationFrame == 1) koopaFrame = 0;
		}
	}
}

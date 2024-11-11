#include "Mushroom.h"
#include "Game.h"

Mushroom::Mushroom(Game* g, Point2D<double> p)
	: game(g), position(p)
{
	position.setY(position.getY() * 32);
	position.setX(position.getX() * 32);
	position = position - Point2D<double>(0, 1); // coloca bien al goomba
	direction = Vector2D<int>(0, 0);

	alive = true;
	texture = game->getTexture(Game::MUSHROOM);
}

void Mushroom::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (position.getX() ) - game->getMapOffset();
	destRect.y = (position.getY() - destRect.h);

	texture->renderFrame(destRect, 0, 0);
}

void Mushroom::update()
{
	moveSeta();
	cout << position << endl;
}

void Mushroom::updateRect()
{
	destRect.h = texture->getFrameHeight() * 2;
	destRect.w = texture->getFrameWidth() * 2;
	destRect.x = position.getX() * TILE_SIDE;
	destRect.y = position.getY() * TILE_SIDE;
}

void Mushroom::moveSeta()
{
	direction = Vector2D<int>(-1, 0);
	position.setX(position.getX() + (direction.getX() * GOOMBA_SPEED * 0.3));
}

Collision Mushroom::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;

	// si hay colision
	if (SDL_HasIntersection(&rect, &destRect))
	{
		c.collides = true;

		// si se origina en mario...
		if (fromPlayer)
		{
			c.evolMario = true;
		}
		// si no... con el tilemap
		else
		{
			// choca por la izq -> va a der
			if(destRect.x <= (rect.x + rect.w))
			{
				direction.setX(1);
			}
			// choca por la der -> va a izq
			else if((destRect.x + destRect.w) >= rect.x)
			{
				direction.setX(-1);
			}
		}
	}

	return c;
}

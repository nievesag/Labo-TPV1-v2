#include "Mushroom.h"
#include "Game.h"
#include "Collision.h"

Mushroom::Mushroom(Game* g, Point2D<double> pos, Texture* texture)
	: Pickable(g, pos, texture)
{
	game = g;
	position = pos;

	position.setY(position.getY() * 32);
	position.setX(position.getX() * 32);
	position = position - Point2D<double>(0, 1); 
	direction = Vector2D<int>(0, 0);

	alive = true;
	texture = game->getTexture(Game::MUSHROOM);
}


void Mushroom::update()
{
	moveSeta();
}


void Mushroom::moveSeta()
{

	direction = Vector2D<int>(-1, 0);
	new_position.setX(position.getX() + (direction.getX() * ENEMY_SPEED * 20));
	new_position.setY(position.getY());

	new_rect.h = destRect.h;
	new_rect.w = destRect.w;
	new_rect.x = new_position.getX();
	new_rect.y = new_position.getY();

	// si no hay colision -> actualiza la posicion
	if (!(game->checkCollisions(new_rect, Collision::Target::ENEMIES).collides))
	{
		position.setX(new_position.getX());
		position.setY(new_position.getY());

		destRect.h = texture->getFrameHeight() * 2;
		destRect.w = texture->getFrameWidth() * 2;
		destRect.x = position.getX();
		destRect.y = position.getY();
	}
	else
	{
		//direction.setX(direction.getX() * -1);
	}
}

Collision Mushroom::hit(const SDL_Rect& rect, Collision::Target t)
{
	Collision c = Pickable::hit(rect, t);

	// si hay colision
	if (SDL_HasIntersection(&rect, &destRect))
	{
		c.collides = true;

		// si se origina en mario...
		if (t == Collision::PLAYER)
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

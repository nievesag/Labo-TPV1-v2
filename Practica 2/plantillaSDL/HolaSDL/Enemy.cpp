#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* g, Point2D<int> p, Texture* t)
	: SceneObject(g, p, t)
{
    direction = Vector2D<int>(0, 0);
}


void Enemy::update() 
{
	c = tryToMove(speed, Collision::PLAYER);

	if (speed.getY() < SPEED_LIMIT)
		speed = speed + Vector2D<int>(0, GRAVITY);

	if (c.vertical) speed.setY(0);
	if (c.horizontal) speed.setX(-speed.getX()); // cambio de direccion

	if (speed.getX() > 0) flip = SDL_FLIP_NONE;
	else if (speed.getX() < 0) flip = SDL_FLIP_HORIZONTAL;
}



Collision Enemy::hit(const SDL_Rect& rect, Collision::Target t)
{
	// Calcula la intersecci�n
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &rect, &intersection);

	if (hasIntersection) 
	{
		Collision collision{Collision::EMPTY, Collision::OBSTACLE, intersection.w, intersection.h };

		// si se origina en mario...
		if (t == Collision::ENEMIES)
		{
			collision.result = Collision::DAMAGE;

			// si la colision es por: arr -> muere el enemigo
			if (((rect.y + rect.h) <= destRect.y + 1))
			{
				collision.target = Collision::ENEMIES;
			}

			// otra colision -> hiere a mario
			else 
			{
				collision.target = Collision::PLAYER;
			}
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

		return collision;
	}

	return NO_COLLISION;
}

Collision Enemy::tryToMove(Vector2D<int>& v, Collision::Target t)
{
	return Collision();
}

void Enemy::collisionResult()
{

}

void Enemy::manageCollisions(Collision collision)
{

}

SceneObject* Enemy::clone() const
{
	return nullptr;
}

void Enemy::updateAnim()
{

}

void Enemy::moveEnemy()
{
    direction = Vector2D<int>(0, 0);

    if (!frozen)
    {
        direction = Vector2D<int>(-1, 0);

        position.setX(position.getX() + (direction.getX() * ENEMY_SPEED * 0.3));
    }
}


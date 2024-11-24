#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* g, Point2D<int> p, Texture* t)
	: SceneObject(g, p, t)
{
    //direction = Vector2D<int>(0, 0);
	setScale(2);

	speed.setX(-3);
}


void Enemy::update() 
{
	// Acelra la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
		speed = speed + Vector2D<int>(0, GRAVITY);

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<int> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	
	// SceneObject::update(); // si hiciera falta
	
}



Collision Enemy::hit(const SDL_Rect& rect, Collision::Target t)
{
	// Calcula la intersecci�n
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &rect, &intersection);

	if (hasIntersection) 
	{
		Collision c{Collision::EMPTY, Collision::OBSTACLE, intersection.w, intersection.h };

		// si se origina en mario...
		if (t == Collision::ENEMIES)
		{
			c.result = Collision::DAMAGE;

			// si la colision es por: arr -> muere el enemigo
			if (((rect.y + rect.h) <= destRect.y + 1))
			{
				c.target = Collision::ENEMIES;
			}

			// otra colision -> hiere a mario
			else 
			{
				c.target = Collision::PLAYER;
			}
		}
		
		return c;
	}

	return NO_COLLISION;
}



void Enemy::collisionResult()
{

}

void Enemy::manageCollisions(Collision c)
{

}

SceneObject* Enemy::clone() const
{
	return nullptr;
}

void Enemy::updateAnim()
{

}




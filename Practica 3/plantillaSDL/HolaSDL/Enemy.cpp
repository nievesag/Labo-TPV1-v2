#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* g, Point2D<int> p, Texture* t, Vector2D<int> s, PlayState* play)
	: SceneObject(g, p, t, s, play)
{
	setScale(2);
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
	{
		if (flip == SDL_FLIP_HORIZONTAL)
		{
			speed.setX(-speed.getX());
			flip = SDL_FLIP_NONE;
		}
		else if(flip == SDL_FLIP_NONE)
		{
			speed.setX(-speed.getX());
			flip = SDL_FLIP_HORIZONTAL;
		}
		
	}


	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	// SceneObject::update(); // si hiciera falta
}

Collision Enemy::hit(const SDL_Rect& rect, Collision::Target t)
{
	// Calcula la interseccion
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &rect, &intersection);

	if (hasIntersection) 
	{
		Collision c{Collision::EMPTY, Collision::NONE, intersection.w, intersection.h };

		// si se origina en mario...
		if (t == Collision::ENEMIES)
		{
			c.result = Collision::DAMAGE;

			// si la colision es por: arr -> muere el enemigo
			if (((rect.y) >= destRect.y - destRect.h) && rect.y != destRect.y)
			{
				c.target = Collision::ENEMIES;
				delete this;
				cout << "pega enemigo arriba" << endl;
			}

			// otra colision -> hiere a mario
			else
			{
				c.target = Collision::PLAYER;
				cout << "au" << endl;
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

void Enemy::updateAnim()
{

}
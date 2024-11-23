#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* g, Point2D<double> position, Texture* t)
	: SceneObject(g, position, t), texture(t)
{
    direction = Vector2D<int>(0, 0);
	game = g;
	//position = pos;
}

void Enemy::render() const {

    SDL_Rect destRect;
    destRect.w = texture->getFrameWidth() * 2;
    destRect.h = texture->getFrameHeight() * 2;
    destRect.x = (position.getX() * TILE_SIDE) - game->getMapOffset();
    destRect.y = position.getY() * TILE_SIDE;

    texture->renderFrame(destRect, 0, animationFrame);
}

void Enemy::update() 
{
	// ----- ruben
	
	// Acelera la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
	{
		speed.setX(speed.getX());
		speed.setY(speed.getY() + GRAVITY);
	}

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<double> realSpeed = speed;

	if (moveDelay-- == 0)
	{
		moveDelay = MOVE_PERIOD;
	}
	else
	{
		realSpeed.setX(0);
	}

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de dirección
	if (collision.horizontal)
		speed.setX(-speed.getX());

	// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
	if (collision.vertical)
		speed.setY(0);

	// SceneObject::update(); // si hiciera falta
	

	// ----- nuestro
    if ((position.getX() * TILE_SIDE) - texture->getFrameWidth() * 2.8 <
        (game->getMapOffset() + game->getWinWidth())) {
        frozen = false;
    }
    moveEnemy();
    animate();
}

void Enemy::updateRect()
{
}

Collision Enemy::hit(const SDL_Rect& rect, Collision::Target t)
{
	// Calcula la intersección
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

Collision Enemy::tryToMove(Vector2D<double> v, Collision::Target t)
{
	return Collision();
}

void Enemy::collisionResult()
{

}

void Enemy::manageCollisions(Collision collision)
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

void Enemy::animate() 
{
    frameTimer++;
    if (frameTimer >= 1200) {
        frameTimer = 0;
        animationFrame = (animationFrame + 1) % 2;
    }
}
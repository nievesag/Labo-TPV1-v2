#include "Enemy.h"
#include "Game.h"

Enemy::Enemy(Game* g, std::istream& in) 
    : SceneObject(g, in) 
{
    direction = Vector2D<int>(0, 0);
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
    if ((position.getX() * TILE_SIDE) - texture->getFrameWidth() * 2.8 <
        (game->getMapOffset() + game->getWinWidth())) {
        frozen = false;
    }
    moveEnemy();
    animate();
}

Collision Enemy::hit(const SDL_Rect& rect, bool fromPlayer) {
	Collision c;

	// si hay colision
	if (SDL_HasIntersection(&rect, &destRect))
	{
		c.collides = true;

			// si se origina en mario...
			if (fromPlayer)
			{
				// si la colision es por: arr -> muere el enemigo
				if (((rect.y + rect.h) <= destRect.y + 1))
				{
					c.damages = false;
				}

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

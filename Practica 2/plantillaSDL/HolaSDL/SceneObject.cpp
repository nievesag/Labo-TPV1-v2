#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* game, Vector2D<int> pos, Texture* texture)
    : GameObject(game), position(pos), scale(1),
    speed(0, 0), texture(texture), isAlive(true), destRect(),
    frame(0), frameTimer(0)
{
    width = TILE_SIDE;
    height = TILE_SIDE;
}

void SceneObject::render()
{
   

    destRect.x = position.getX() - game->getMapOffset();
    destRect.h = (texture->getFrameHeight() * scale);
    destRect.w = texture->getFrameWidth() * scale;
   

    if (texture == game->getTexture(Game::SUPERMARIO))
    {
        destRect.y = position.getY() - TILE_SIDE / 2;
    }
    else
    {
        destRect.y = position.getY();
    }


    texture->renderFrame(destRect, 0, frame, 0, nullptr, flip);
}

SDL_Rect SceneObject::getCollisionRect() const
{
    return SDL_Rect{
        position.getX(),
        position.getY(), // - _height,
        width,
        height
    };
}

SDL_Rect SceneObject::getRenderRect() const
{
    return SDL_Rect{
        position.getX() - game->getMapOffset(),
        position.getY() - height,
        width,
        height
    };
}

void SceneObject::manageCollisions(Collision c)
{
}

Collision SceneObject::tryToMove(const Vector2D<int>& speed, Collision::Target target)
{
    // Enunciado
    Collision c;
    SDL_Rect rect = getCollisionRect();

    // Movimiento vertical
    if (speed.getY() != 0) {
        rect.y += speed.getY();
        c = game->checkCollisions(rect, target);

        // Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
        int fix = c.vertical * (speed.getY() > 0 ? 1 : -1);
        //position += {0, speed.getY() - fix};
        position = position + Vector2D<int>(0, speed.getY() - fix);

        rect.y -= fix; // recoloca la caja para la siguiente colisión
    }

    c.horizontal = 0;

    // Intenta moverse en horizontal
    // (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
    if (speed.getX() != 0) {
        rect.x += speed.getX();

        Collision partial = game->checkCollisions(rect, target);

        // Copia la información de esta colisión a la que se devolverá
        c.horizontal = partial.horizontal;

        if (partial.result == Collision::DAMAGE)
            c.result = Collision::DAMAGE;

        //position += {speed.getX() - c.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
        position = position + Vector2D<int>(speed.getX() - c.horizontal * (speed.getX() > 0 ? 1 : -1), 0);
    }

    return c;
}

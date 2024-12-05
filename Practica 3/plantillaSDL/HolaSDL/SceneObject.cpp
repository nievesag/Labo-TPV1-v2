#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* g, Vector2D<int> pos, Texture* t)
    : GameObject(g), position(pos), texture(t), scale(1), isAlive(true), destRect(),
    frame(0), frameTimer(0)
{
    width = TILE_SIDE;
    height = TILE_SIDE;
}

SceneObject::SceneObject(Game* game, Vector2D<int> pos, Texture* texture, Vector2D<int> s)
    : GameObject(game), position(pos),  texture(texture), scale(1), isAlive(true), destRect(),
    speed(s), frame(0), frameTimer(0)
{
	width = TILE_SIDE;
	height = TILE_SIDE;
}

SceneObject::SceneObject(const SceneObject& s)
{
    game = s.game;

    // movimiento
	position = s.position;
	speed = s.speed;
	direction = s.direction;

    // representacion
	width = s.width;
	height = s.height;
	texture = s.texture;
	flip = s.flip;
	flipSprite = s.flipSprite;
	scale = s.scale;
	destRect = s.destRect;

    // animacion
	frame = s.frame;
	frameTimer = s.frameTimer;

    // logica
    isAlive = s.isAlive;
	c = s.c;
	canMove = s.canMove;
}

SceneObject& SceneObject::operator=(const SceneObject& s)
{
	if(this != &s)
	{
        game = s.game;

        // movimiento
        position = s.position;
        speed = s.speed;
        direction = s.direction;

        // representacion
        width = s.width;
        height = s.height;
        texture = s.texture;
        flip = s.flip;
        flipSprite = s.flipSprite;
        scale = s.scale;
        destRect = s.destRect;

        // animacion
        frame = s.frame;
        frameTimer = s.frameTimer;

        // logica
        isAlive = s.isAlive;
        c = s.c;
        canMove = s.canMove;
	}
	return *this;
}

void SceneObject::render() const
{
    // QUE CADA OBJETO TENGA SU RENDER
    // HACER METODO UPDATERECT PARA MODIFICAR LOS ATRIBUTOS DEL DESTRECT PORQ AHORA RENDER ES CONST

    destRect.x = position.getX() - game->getMapOffset();
    destRect.h = texture->getFrameHeight() * scale;
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
        position.getY(),
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

void SceneObject::handleEvent(const SDL_Event& event)
{

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

        // Cantidad que se ha entrado en el obst�culo (lo que hay que deshacer)
        int fix = c.vertical * (speed.getY() > 0 ? 1 : -1);
        //position += {0, speed.getY() - fix};
        position = position + Vector2D<int>(0, speed.getY() - fix);

        rect.y -= fix; // recoloca la caja para la siguiente colisi�n
    }

    c.horizontal = 0;

    // Intenta moverse en horizontal
    // (podr�a ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
    if (speed.getX() != 0) {
        rect.x += speed.getX();

        Collision partial = game->checkCollisions(rect, target);

        // Copia la informaci�n de esta colisi�n a la que se devolver�
        c.horizontal = partial.horizontal;

        if (partial.result == Collision::DAMAGE)
            c.result = Collision::DAMAGE;

        //position += {speed.getX() - c.horizontal * (speed.getX() > 0 ? 1 : -1), 0};
        position = position + Vector2D<int>(speed.getX() - c.horizontal * (speed.getX() > 0 ? 1 : -1), 0);
    }

    return c;
}
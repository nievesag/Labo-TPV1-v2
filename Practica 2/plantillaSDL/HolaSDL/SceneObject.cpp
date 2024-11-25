#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* game, Vector2D<int> pos, Texture* texture)
    : GameObject(game), position(pos), scale(1),
    speed(0, 0), texture(texture), _isAlive(true), destRect(),
    frame(0), frameTimer(0)
{
	width = TILE_SIDE;
	height = TILE_SIDE;

}

SceneObject::SceneObject(Game* g, Point2D<int> pos, Texture* t, Vector2D<int> s)
	: GameObject(g), position(pos), speed(s), texture(t), frame(0), frameTimer(0), destRect()
{
	speed.setX(0);
	speed.setY(0);
}

SceneObject::SceneObject(const SceneObject& s)
{
	position = s.position;
	width = s.width;
	height = s.height;
	speed = s.speed;
	direction = s.direction;
	canMove = s.canMove;
	texture = s.texture;
	frame = s.frame;
	flip = s.flip;
	frameTimer = s.frameTimer;
	flipSprite = s.flipSprite;
	scale = s.scale;
	c = s.c;
	destRect = s.destRect;

	//setListAnchor(_anchor);
}

SceneObject& SceneObject::operator=(const SceneObject& s)
{
	if(this != &s)
	{
		position = s.position;
		width = s.width;
		height = s.height;
		speed = s.speed;
		direction = s.direction;
		canMove = s.canMove;
		texture = s.texture;
		frame = s.frame;
		flip = s.flip;
		frameTimer = s.frameTimer;
		flipSprite = s.flipSprite;
		scale = s.scale;
		c = s.c;
		destRect = s.destRect;

		//setListAnchor(_anchor);
	}
	return *this;
}

// concentra la comprobacion de colisiones para todos los objetos del juego
// tryToMove(vector movimiento que se quiere aplicar al objeto, a quien afecta la colision)
// -> prueba el movimiento en ambos ejes y devuelve la informacion de tipo Collision
Collision SceneObject::tryToMove(Vector2D<int>& v, Collision::Target target)
{
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.getY() != 0)
	{
		rect.y += speed.getY();

		collision = game->checkCollisions(rect, target);

		// Cantidad que se ha entrado en el obstaculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		position.setX(position.getX() + 0);
		position.setY(speed.getY() - fix);

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

		rect.y -= fix; // recoloca la caja para la siguiente colision

		
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	// (podr�a ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
	if (speed.getX() != 0) 
	{
		rect.x += speed.getX();

		Collision partial = game->checkCollisions(rect, target);

		

		// Copia la informaci�n de esta colisi�n a la que se devolver�
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE) collision.result = Collision::DAMAGE;
		
		position.setX(speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1));
		position.setY(position.getY() + 0);

		
	}

	return collision;
}


void SceneObject::render()
{
    destRect.x = position.getX() - game->getMapOffset();
    destRect.y = position.getY();
    destRect.w = texture->getFrameWidth() * scale;
    destRect.h = texture->getFrameHeight() * scale;

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

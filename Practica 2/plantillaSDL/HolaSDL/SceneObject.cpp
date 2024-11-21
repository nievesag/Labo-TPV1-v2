#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* g, Point2D<int> pos, int width, int heigth, Texture* texture)
	: GameObject(g), position(pos), _width(width), _height(height), speed(0,0), texture(texture)
{
	if(texture != nullptr)
	{
		destRect.h = texture->getFrameHeight();
		destRect.w = texture->getFrameWidth();
		destRect.x = position.getX();
		destRect.y = position.getY();
	}
}

// concentra la comprobacion de colisiones para todos los objetos del juego
// tryToMove(vector movimiento que se quiere aplicar al objeto, a quien afecta la colision)
// -> prueba el movimiento en ambos ejes y devuelve la informacion de tipo Collision
Collision SceneObject::tryToMove(Vector2D<double> v, Collision::Target target)
{
	Collision collision;
	SDL_Rect rect = getCollisionRect();

	// Intenta moverse en vertical
	if (speed.getY() != 0)
	{
		rect.y += speed.getY();

		collision = game->checkCollisions(rect, target);

		// Cantidad que se ha entrado en el obstáculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		position.setX(position.getX() + 0);
		position.setY(speed.getY() - fix);

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

		rect.y -= fix; // recoloca la caja para la siguiente colisión
	}

	collision.horizontal = 0; // la horizontal del choque vertical da igual

	// Intenta moverse en horizontal
	// (podría ser conveniente comprobar colisiones incluso aunque el objeto estuviera parado)
	if (speed.getX() != 0) 
	{
		rect.x += speed.getX();

		Collision partial = game->checkCollisions(rect, target);

		// Copia la información de esta colisión a la que se devolverá
		collision.horizontal = partial.horizontal;

		if (partial.result == Collision::DAMAGE)
			collision.result = Collision::DAMAGE;
		
		position.setX(speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1));
		position.setY(position.getY() + 0);
	}

	return collision;
}

SDL_Rect SceneObject::getCollisionRect() const
{
	return SDL_Rect{
		position.getX(),
		position.getY() - height,  // la referencia es la esquina inferior izquierda
		width,
		height
	};
}

SDL_Rect SceneObject::getRenderRect() const
{
	return SDL_Rect{
		position.getX() - game->getMapOffset(),  // coordenadas de la ventana
		position.getY() - height,
		width,
		height
	};
}
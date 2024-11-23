#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* g, Point2D<double> pos, Texture* t)
	: GameObject(g), position(pos), texture(t)
{
	speed = Vector2D<double>(0, 0);
	if (texture != nullptr) 
	{
		destRect.h = texture->getFrameHeight();
		height = destRect.h;
		destRect.w = texture->getFrameWidth();
		width = destRect.w;
		destRect.x = position.getX();
		destRect.y = position.getY();
	}
	game = g;
	direction = Vector2D<int>(0, 0);
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

		// Cantidad que se ha entrado en el obstaculo (lo que hay que deshacer)
		int fix = collision.vertical * (speed.getY() > 0 ? 1 : -1);
		position.setX(position.getX() + 0);
		position.setY(speed.getY() - fix);

		// Obs: a ? b : c es el operador ternario: vale b si a es cierto y c en caso contrario

		rect.y -= fix; // recoloca la caja para la siguiente colision
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

		if (partial.result == Collision::DAMAGE) collision.result = Collision::DAMAGE;
		
		position.setX(speed.getX() - collision.horizontal * (speed.getX() > 0 ? 1 : -1));
		position.setY(position.getY() + 0);
	}

	return collision;
}

SDL_Rect SceneObject::getCollisionRect() const
{
	SDL_Rect collRect;

	collRect.x = position.getX();
	collRect.y = position.getY() - height; // la referencia es la esquina inferior izquierda
	collRect.w = width;
	collRect.h = height;

	return collRect;
}

SDL_Rect SceneObject::getRenderRect() const
{
	SDL_Rect renderRect;

	renderRect.x = position.getX() - game->getMapOffset(); // coordenadas de la ventana
	renderRect.y = position.getY() - height;
	renderRect.w = width;
	renderRect.h = height;

	return renderRect;
}
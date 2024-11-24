#include "SceneObject.h"
#include "Game.h"

SceneObject::SceneObject(Game* g, Point2D<int> pos, Texture* t)
	: GameObject(g), position(pos), texture(t), frame(0), frameTimer(0), 
	destRect(), speed(0, 0)
{
	width = TILE_SIDE;
	height = TILE_SIDE;

	speed.setX(0);
	speed.setY(0);
	if (texture != nullptr) 
	{
		destRect.h = texture->getFrameHeight();
		height = destRect.h;
		destRect.w = texture->getFrameWidth();
		width = destRect.w;
		destRect.x = position.getX();
		destRect.y = position.getY();
	}
	direction = Vector2D<int>(0, 0);
	canMove = true;

	// construir el anchor de la copia
	// (indica que el objeto no esta incluido todavia en la lista de objetos del juego) :

}

SceneObject::SceneObject(Game* g, Point2D<int> pos, Texture* t, Vector2D<int> s)
	: GameObject(g), position(pos), speed(s), texture(t), frame(0), frameTimer(0), destRect()
{
	speed.setX(0);
	speed.setY(0);
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
	

	SDL_Rect collRect;

	collRect.x = position.getX();
	collRect.y = position.getY(); // la referencia es la esquina inferior izquierda
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
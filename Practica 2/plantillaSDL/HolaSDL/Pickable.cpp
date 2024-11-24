#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* g, Point2D<int> p, Texture* t)
	: SceneObject(g, p, t)
{
	
}

void Pickable::render()
{
	texture->renderFrame(destRect, 0, 0);
}

void Pickable::update()
{
	updateRect();
	game->checkCollisions(destRect, Collision::PLAYER);
}

void Pickable::updateRect()
{
	// tamanio
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (position.getX()) - game->getMapOffset();
	destRect.y = (position.getY() - destRect.h);
}

Collision Pickable::hit(const SDL_Rect& rect, Collision::Target t)
{
	// Comprueba si hay colision
	SDL_Rect ownRect = getCollisionRect();

	// si la colision es con el mario (su target son los enemies)
	if (t == Collision::ENEMIES && SDL_HasIntersection(&ownRect, &rect)) 
	{
		triggerAction();  // metodo que implementara la subclase
		delete this;
	}

	return NO_COLLISION; // constante Collision{}
}

void Pickable::manageCollisions(Collision collision)
{

}
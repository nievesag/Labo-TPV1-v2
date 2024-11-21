#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* g, Point2D<double> p)
	: SceneObject(g, p)
{

}

void Pickable::render() const
{
	SDL_Rect destRect;

	// tamanio
	destRect.w = texture->getFrameWidth() * 2;
	destRect.h = texture->getFrameHeight() * 2;

	// posicion
	destRect.x = (position.getX()) - game->getMapOffset();
	destRect.y = (position.getY() - destRect.h);

	texture->renderFrame(destRect, 0, 0);
}

void Pickable::update()
{
	updateRct();
}

void Pickable::updateRct()
{
	destRect.h = texture->getFrameHeight() * 2;
	destRect.w = texture->getFrameWidth() * 2;
	destRect.x = position.getX();
	destRect.y = position.getY();
}

Collision Pickable::hit(const SDL_Rect& rect, bool fromPlayer)
{
	
}

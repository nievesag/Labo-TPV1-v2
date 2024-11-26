#include "Pickable.h"
#include "Game.h"

Pickable::Pickable(Game* g, Point2D<int> p, Texture* t)
	: SceneObject(g, p, t)
{
	
}

void Pickable::update() {}

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

void Pickable::manageCollisions(Collision c) {}

SceneObject* Pickable::clone() const
{
	return nullptr;
}

void Pickable::updateAnim() {}
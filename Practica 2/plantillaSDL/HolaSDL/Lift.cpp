#include "Lift.h"
#include "Game.h"
#include "Collision.h"

Lift::Lift(Game* g, Point2D<int> p, Texture* t, Vector2D<int> s)
	: SceneObject(g, p, t, s)
{
	direction = Vector2D<int>(0, 1);
}

void Lift::render()
{
	texture->render(destRect);
}

void Lift::update()
{
	moveLift();
}

void Lift::updateAnim()
{

}


SceneObject* Lift::clone() const
{
	return new Lift(*this);
}

Collision Lift::hit(const SDL_Rect& rect, Collision::Target t)
{
	return Collision();
}

void Lift::manageCollisions(Collision collision)
{
}

void Lift::moveLift()
{
	// siendo la y la base del objeto(?)

	// se sale por abajo || se sale por arriba
	if(position.getY() > game->getWinHeight() || position.getY() + destRect.h < 0)
	{
		direction.setY(direction.getY() * -1);
	}

	position.setY(position.getY() + (direction.getY() * speed.getY()));
}
#include "Mushroom.h"
#include "Game.h"
#include "Collision.h"

Mushroom::Mushroom(Game* g, Point2D<int> p, Texture* t)
	: Pickable(g, p, t)
{
	setScale(2);
	speed.setX(3);
}

void Mushroom::render()
{
	Pickable::render();
}

void Mushroom::update()
{
	moveSeta();
}

void Mushroom::moveSeta()
{
	// Acelra la velocidad con la gravedad
	if (speed.getY() < SPEED_LIMIT)
		speed = speed + Vector2D<int>(0, GRAVITY);

	// Velocidad en este ciclo (no siempre avanza lateralmente)
	Vector2D<int> realSpeed = speed;

	if (moveDelay-- == 0)
		moveDelay = MOVE_PERIOD;
	else
		realSpeed.setX(0);

	// Intenta moverse
	Collision collision = tryToMove(realSpeed, Collision::PLAYER);

	// Si toca un objeto en horizontal cambia de direcci�n
	if (collision.horizontal)

		// Si toca un objeto en vertical anula la velocidad (para que no se acumule la gravedad)
		if (collision.vertical)
			speed.setY(0);

	// SceneObject::update(); // si hiciera falta
}

void Mushroom::triggerAction()
{

}

SceneObject* Mushroom::clone() const
{
	return nullptr;
}
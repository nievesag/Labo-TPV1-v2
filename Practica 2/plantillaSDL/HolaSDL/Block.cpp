#include "Block.h"
#include "Game.h"

Block::Block(Game* g, Point2D<int> position, Texture* t, char tipoL, char accionL)
	: SceneObject(g, position, t)
{
	game = g;
	frame = 0;
	// Asignamos el tipo de bloque basado en el car�cter le�do
	switch (tipoL) {
	case 'B':
		tipo = LADRILLO;
		frame = 5;
		break;
	case '?':
		tipo = SORPRESA;
		frame = 0;  // Comienza la animaci�n del bloque sorpresa desde el primer frame
		break;
	case 'H':
		tipo = OCULTO;
		frame = 4;
		break;
	}

	// Asignamos la acci�n del bloque basado en el car�cter le�do
	switch (accionL) {
	case 'P':
		accion = POTENCIADOR;
		break;
	case 'C':
		accion = MONEDA;
		break;
	}

	alive = true;
}

void Block::render()
{
}


void Block::update()
{
	updateAnim();
}



Collision Block::hit(const SDL_Rect& rect, Collision::Target t)
{
	/*
	Collision c;

	// si hay colision
	if (SDL_HasIntersection(&rect, &destRect))
	{
		c.collides = true;
		c.damages = false;

		// si se origina en mario...
		if (t == Collision::PLAYER)
		{
			// si la colision es por: abj 
			if (rect.y <= (destRect.y + destRect.h))
			{
				if (tipo == LADRILLO && (game->getMarioState() == 1)) 
				{
					c.killBrick = true;
				}
				else if (tipo == SORPRESA || tipo == OCULTO)
				{
					c.spawnSeta = true;
				}
			}
			else if ((rect.y + rect.h) <= destRect.y) {
			
				c.setGrounded = true;
			}
		}
		// si con otras entidades...
		else
		{

		}
	}

	return c;
	*/

	// Calcula la intersecci�n
	SDL_Rect intersection;
	SDL_Rect ownRect = getCollisionRect();
	bool hasIntersection = SDL_IntersectRect(&ownRect, &rect, &intersection);

	if (hasIntersection) 
	{
		Collision collision{ Collision::EMPTY, Collision::OBSTACLE, intersection.w, intersection.h };

		// [...] Manejo del efecto del bloque
		//c.collides = true;
		//c.damages = false;
		
		// si se origina en mario...
		if (t == Collision::ENEMIES)
		{
			// si la colision es por: abj 
			if (rect.y <= (destRect.y + destRect.h))
			{
				if (tipo == LADRILLO && (game->getMarioState() == 1))
				{
					//c.killBrick = true;
				}
				else if (tipo == SORPRESA || tipo == OCULTO)
				{
					//c.spawnSeta = true;
				}
			}
			else if ((rect.y + rect.h) <= destRect.y) {

				//c.setGrounded = true;
			}
		}
		// si con otras entidades...
		else
		{

		}

		return collision;
	}

	return NO_COLLISION;
}

void Block::manageSorpresa()
{
	setTipo(3);
	frame = 4;
}

void Block::manageCollisions(Collision collision)
{

}

SceneObject* Block::clone() const
{
	return nullptr;
}

void Block::updateAnim()
{
	if (tipo == SORPRESA) {
		frameTimer++;
		if (frameTimer >= 3050) {  // Velocidad del ciclo
			frameTimer = 0;
			frame = (frame + 1) % 3;  // Ciclo 0,1,2,3, y luego se reinicie 

			// Ciclo de caminar 2 -> 3 -> 4 -> 3
			if (frame == 0) frame = 1;
			else if (frame == 1) frame = 2;
			else if (frame == 2) frame = 0;
		}
	}
}

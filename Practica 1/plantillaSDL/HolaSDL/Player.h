#ifndef PLAYER_H
#define PLAYER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"
#include <istream>

// es una promesa de la existencia de la clase game
// para evitar inclusiones cruzadas
class Game;

using uint = unsigned int;

class Player
{
	// atributos privados
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	int lives;					// numero de vidas restantes, 3 al inicio

	// MOVIMIENTO
	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<double> direction;	// direccion de movimiento
	float speed = 0.05;			// velocidad de movimiento

	// input
	bool keyA = false, keyD = false, keySpace = false;

	// rect destino
	SDL_Rect destRect;
public:
	Player();
	Player(Game* game, std::istream& in);
};

#endif	
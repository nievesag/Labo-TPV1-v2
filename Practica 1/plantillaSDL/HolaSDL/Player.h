#ifndef PLAYER_H
#define PLAYER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"
#include <istream>

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

	// INPUT
	// flags para control de input
	bool keyA = false, keyD = false, keyS = false, keySpace = false, keyE = false;

	// rect destino
	SDL_Rect destRect;

public:
	Player(Game* g, std::istream& i); // no se si pasarle la textura

	// -- render --
	void render() const;

	// -- update --
	// movimiento:
	// Es importante no realizar la actualizacion de la pos directamente
	// al pulsar la tecla, sino a traves de la dir, porque si no Mario se desplazara a trompicones
	// Si se pulsa la barra espaciadora y esta apoyado sobre un obstaculo, Mario saltara hasta
	// alcanzar una determinada altura o colisionar con un objeto, momento en el que empezara a caer
	void update();

	// -- handleEvent --     
	void handleEvent(const SDL_Event& event);

	// -- hit --
	void hit(SDL_Rect* rect);

	//
	void updateRect();

private:
	void moveMario();
};

#endif	
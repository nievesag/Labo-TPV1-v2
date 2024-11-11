#ifndef PLAYER_H
#define PLAYER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"

// para evitar inclusiones cruzadas
class Game;

using uint = unsigned int;
using namespace std;

class Player
{
	// atributos privados
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	int maxLives = 3;
	int lives;					// numero de vidas restantes, 3 al inicio

	bool isAlive = true;

	// MOVIMIENTO
	Point2D<double> position;	// posicion actual en Point2D
	Vector2D<int> direction;	// direccion de movimiento
	float speed = 0.05;			// velocidad de movimiento

	bool grounded;		// si esta en el suelo, solo puede saltar cuando lo este
	double groundedYPos;	// posicion en el suelo
	double maxHeight;
	
	int marioState;
	enum State {
		MARIO, SUPERMARIO
	};

	// ANIMACION
	int marioFrame;

	// INPUT
	// flags para control de input
	bool keyA = false, keyD = false, keyS = false, keySpace = false, keyE = false, keyDer = false;

	// rect destino
	SDL_Rect destRect;

	bool isFalling = false;
	bool canJump = false;
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;
	bool flipSprite = false;
	bool moving = false;

	//Colisiones
	Point2D<double> new_position;	// posicion que tendria si avanza en Point2D
	SDL_Rect new_rect;				// rect que tendria si avanza en Point2D
	SDL_Rect collider;
	Collision c;

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
	void handleEvents(const SDL_Event& event);

	// -- hit --
	Collision hit(const SDL_Rect& rect, bool fromPlayer);

	//
	void updateAnims();

	void updateOffset();

	void handleMovement();

	int getState() {
		return marioState;
	}

	void setState(int s) {
		marioState = s;
	}

private:
	void moveMario();

	bool checkFall();

	// para comprobar los moviemientos antes de ejecutarlos por si hubiese colision
	// devuelven true si se pueden hacer los movimientos
	// DERECHA
	bool checkMovDer();
	// IZQUIERDA
	bool checkMovIzq();
	// ARRIBA
	bool checkMovArr();
};

#endif	
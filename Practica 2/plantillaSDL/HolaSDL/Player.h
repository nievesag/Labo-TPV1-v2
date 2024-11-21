#ifndef PLAYER_H
#define PLAYER_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "SceneObject.h"

// para evitar inclusiones cruzadas
class Game;

using uint = unsigned int;
using namespace std;

class Player : public SceneObject
{
	// atributos privados
private:
	Texture* texture = nullptr;	// puntero a su textura
	Texture* textureM = nullptr;
	Texture* textureS = nullptr;
	Game* game = nullptr;		// puntero al juego

	int maxLives = 3;
	int lives;					// numero de vidas restantes, 3 al inicio

	bool alive = true;

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

	// invencibilidad
	int invCounter = 0;
	int maxInvCounter = 5;
	bool invencible = false;

public:
	Player(Game* g, std::istream& i); // no se si pasarle la textura

	// -- render --
	void render() const override;

	// -- update --
	// movimiento:
	// Es importante no realizar la actualizacion de la pos directamente
	// al pulsar la tecla, sino a traves de la dir, porque si no Mario se desplazara a trompicones
	// Si se pulsa la barra espaciadora y esta apoyado sobre un obstaculo, Mario saltara hasta
	// alcanzar una determinada altura o colisionar con un objeto, momento en el que empezara a caer
	void update() override;

	void updateTexture();

	// -- handleEvent --     
	void handleEvents(const SDL_Event& event);

	// -- hit --
	Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	Collision tryToMove(Vector2D<double> v, Collision::Target t) override;

	void manageDamage();

	void manageInvencible();

	void updateAnims();

	void updateOffset();

	void updateRect();

	int getState() {
		return marioState;
	}

	void setState(int s) {
		marioState = s;
	}

	bool getAlive() {
		return alive;
	}

	void setGrounded(bool g) {
		grounded = g;
	}


private:
	void moveMario();

	bool checkFall();
};

#endif	
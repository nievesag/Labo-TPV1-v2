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
//#include "Game.h"
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
	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	int maxLives = 3;
	int lives;					// numero de vidas restantes, 3 al inicio
	bool alive = true;
	
	
	int marioState;
	enum State {
		MARIO, SUPERMARIO
	};

	// INPUT
	// flags para control de input
	bool keyA = false, keyD = false, keyS = false, keySpace = false, keyE = false, keyDer = false;

	bool grounded;		// si esta en el suelo, solo puede saltar cuando lo este
	bool jumping;

	bool flipSprite = false;

	// invencibilidad
	int invCounter = 0;
	int maxInvCounter = 5;
	bool invencible = false;

	double deadH = 14*32;
	int bgSpeed = 1;
	int marioFrame;
	int velX;

public:
	Player(Game* g, Point2D<int> p, Texture* t, int l); // no se si pasarle la textura

	// -- render --
	void render() override;

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

	void manageCollisions(Collision collision) override;

	SceneObject* clone() const override;

	void manageDamage();

	void manageInvencible();

	void updateAnim() override;

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

	Vector2D<double> getNextMoveVector();

private:
	void moveMario(bool moveX, bool moveY);

	void checkFall();
};

#endif	
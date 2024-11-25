#ifndef PLAYER_H
#define PLAYER_H

#include "SceneObject.h"

class Player : public SceneObject
{

public:
	Player(Game* game, Vector2D<int> pos);

	void render() override;
	void update() override;

	void updateTexture();

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void resetPlayer();
	void updateAnim() override;
	void jump();

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	void handleEvent(SDL_Event event);

	virtual void manageCollisions(Collision c) override;

	void manageDamage();

	int marioState;
	enum State {
		MARIO, SUPERMARIO
	};

	void finishLevel();

	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	int flagPosition = 6306;


private:
	int lives;
	bool immune;

	bool grounded, jumping;

	int walkFrame;

	// INPUT
	// flags para control de input
	bool keyA = false, keyD = false, keyS = false, keySpace = false, keyE = false, keyDer = false;

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
	Player(Game* g, Point2D<int> p, Texture* t, int l);

	// -- render --
	void render() override;

	// -- update --
	// movimiento:
	// Es importante no realizar la actualizacion de la pos directamente
	// al pulsar la tecla, sino a traves de la dir, porque si no Mario se desplazara a trompicones
	// Si se pulsa la barra espaciadora y esta apoyado sobre un obstaculo, Mario saltara hasta
	// alcanzar una determinada altura o colisionar con un objeto, momento en el que empezara a caer
	void update() override;

	// -- handleEvent --     
	void handleEvent(const SDL_Event& event);

	// -- hit --
	Collision hit(const SDL_Rect& rect, Collision::Target t) override;

	void manageCollisions(Collision collision) override;

	SceneObject* clone() const override;

	void manageDamage();

	void manageInvencible();

	void updateAnim() override;

	void updateOffset();

	int getState() {
		return marioState;
	}

	void setState(int s) {
		marioState = s;
	}

	void setGrounded(bool g) {
		grounded = g;
	}

	void resetPlayer();

	void jump();
};

#endif
#pragma once
#include "SceneObject.h"

class Player : public SceneObject
{

public:
	Player(Game* game, Vector2D<int> pos);

	void render() override;
	void update() override;

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;


	void resetPlayer();
	void updateAnim() override;
	void jump();

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	void isSupermario();
	void handleEvent(SDL_Event event);

	virtual void manageCollisions(Collision c) override;


private:
	int lives;
	bool immune;

	int velX;
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

private:


	void checkFall();

};


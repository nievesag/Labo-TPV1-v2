#ifndef PLAYER_H
#define PLAYER_H

#include "EventHandler.h"
#include "SceneObject.h"

class PlayState;

class Player : public SceneObject, EventHandler
{
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

	PlayState* playState;

public:
	Player(Game* game, Vector2D<int> pos, Texture* t, int l, Vector2D<int> s, PlayState* play);

	void render() const override;
	void update() override;

	void updateTexture();

	Collision hit(const SDL_Rect& region, Collision::Target target) override;
	SceneObject* clone() const override;

	void updateAnim() override;
	void jump();

	int getLives() { return lives; }
	void setLives(int n) { lives = n; }

	int getFrame() { return marioFrame; }

	void handleEvent(const SDL_Event& event) override;

	virtual void manageCollisions(Collision c) override;

	void manageInvencible();

	void manageDamage();

	int marioState;
	enum State {
		MARIO, SUPERMARIO
	};

	void finishLevel();

	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	int flagPosition = 6306;

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

	void checkFall();
};

#endif
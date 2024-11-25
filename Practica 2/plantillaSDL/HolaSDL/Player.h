#pragma once
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

	Texture* textureM = nullptr;
	Texture* textureS = nullptr;

	bool invencible;


private:
	int lives;
	bool immune;

	int velX;
	bool grounded, jumping;

	int walkFrame;

	// INPUT
	// flags para control de input
	bool keyA = false, keyD = false, keyS = false, keySpace = false, keyE = false, keyDer = false;


};
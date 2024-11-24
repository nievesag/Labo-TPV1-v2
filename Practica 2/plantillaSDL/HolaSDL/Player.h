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
	void handleEvent(SDL_Event e);

	virtual void manageCollisions(Collision c) override;


private:
	int lives;
	bool immune;

	int marioSpeed;
	bool onGround, jumping;

	int walkFrame;

};


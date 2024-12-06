#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H
#include "GameState.h"
#include "Player.h"

class AnimationState : public GameState
{
private:
	Player* player;
	GameState* next;

public:
	AnimationState(Game* g, GameState* n, Player* p);

	// renderizado del estado
	void render() const override;

	void update() override;
};

#endif
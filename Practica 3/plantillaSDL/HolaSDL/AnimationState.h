#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H
#include "GameState.h"

class AnimationState : public GameState
{
public:
	AnimationState(Game* game);

	// renderizado del estado
	void render() const override;

	void update() override;
};

#endif
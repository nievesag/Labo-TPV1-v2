#ifndef ANIMATIONSTATE_H
#define ANIMATIONSTATE_H
#include <functional>

#include "Button.h"
#include "GameState.h"
#include "Player.h"

// utiliza callbacks funcionales de tipo <void(void)>
using AnimationCallback = std::function<bool()>;

class AnimationState : public GameState
{
private:
	GameState* actual;

	// lista de funciones a ejecutar al llamarlo
	std::list<AnimationCallback> callbacks;

public:
	AnimationState(Game* g, GameState* a, std::function<bool()> f);

	// renderizado del estado
	void render() const override;

	void update() override;
};

#endif
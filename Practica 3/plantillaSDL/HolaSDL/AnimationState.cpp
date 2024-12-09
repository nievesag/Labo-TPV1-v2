#include "AnimationState.h"

#include "Game.h"

AnimationState::AnimationState(Game* g, GameState* a, std::function<bool()> f)
	: GameState(g), actual(a)
{
	callbacks.push_back(f);
}

void AnimationState::render() const
{
	actual->render();
}

void AnimationState::update()
{
	// llama a todas las funciones registradas
	for (AnimationCallback func : callbacks)
	{
		if(!func())
		{
			// se desapila
			game->getgsMachine()->popState();
		}
	}
}
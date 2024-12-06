#include "AnimationState.h"

#include "Game.h"

AnimationState::AnimationState(Game* g, GameState* n, Player* p)
	: GameState(g), player(p), next(n)
{

}

void AnimationState::render() const
{
	for (auto e : gameList) e->render();
}

void AnimationState::update()
{
	for (auto e : gameList) e->update();

	if(player->getPosition().getY() > game->getWinHeight())
	{
		game->getgsMachine()->pushState(next);
	}
}
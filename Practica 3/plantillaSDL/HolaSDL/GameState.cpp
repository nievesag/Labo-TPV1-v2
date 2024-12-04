#include "GameState.h"

GameState::GameState(Game* game)
{

}

void GameState::render() const
{
}

void GameState::update()
{
}

void GameState::handleEvent(const SDL_Event& event)
{

}

void GameState::addEventListener(EventHandler* l)
{
	eventHandlers.push_back(l);
}

void GameState::addObject(SceneObject* o)
{
	gameList.push_back(o);
}
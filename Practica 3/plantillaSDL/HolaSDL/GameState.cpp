#include "GameState.h"

GameState::GameState(Game* g) : game(g)
{

}

void GameState::render() const
{
	for (auto obj : stateList) {
		obj->render();
	}
}

void GameState::update()
{
	for (auto obj : stateList) {
		obj->update();
	}
}

void GameState::handleEvent(const SDL_Event& event)
{
	for (auto handler : eventHandlers) {
		handler->handleEvent(event);
	}
}

void GameState::addEventListener(EventHandler* l)
{
	eventHandlers.push_back(l);
}

void GameState::addObject(GameObject* o)
{
	stateList.push_back(o);
}
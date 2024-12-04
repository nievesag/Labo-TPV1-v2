#ifndef GAMESTATE_H
#define GAMESTATE_H
#include <list>
#include <SDL_events.h>

#include "EventHandler.h"
#include "gameList.h"
#include "SceneObject.h"

// GameState es propietario de
// los objetos en sus listas de GameObject y debe eliminarlos al destruirse, pero no ocurre así con PlayState
// y los objetos de la lista de SceneObject(pues es una lista redundante)

class Game;

class GameState
{
protected:
	
	Game* game; // referencia al game

	// lista de objetos del juego
	GameList<SceneObject> gameList;

	// lista de punteros a oyentes
	std::list<EventHandler*> eventHandlers;

public:
	GameState(Game* game);

	virtual ~GameState() = default;

	// render del estado
	virtual void render() const;

	// actualiza el estado
	virtual void update();

	// gestiona los eventos del estado
	virtual void handleEvent(const SDL_Event& event);

	// getter del juego
	Game* getGame() const { return game; }

	void addEventListener(EventHandler* l);

	void addObject(SceneObject* o);
};

#endif
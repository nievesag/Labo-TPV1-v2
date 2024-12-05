#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"

class GameState;
class Game;

class GameObject
{
	// atributos protegidos
protected:

	// puntero al game
	Game* game;

	// puntero al estado de juego (no al sdl application, al playState)
	GameState* state;

	// metodos publicos
public:

	GameObject();

	GameObject(Game* g);

	GameObject(GameState* s);

	GameObject(Game* g, GameState* s);

	// destructora virtual
	virtual ~GameObject();

	// ---- render ----
	virtual void render() const = 0;

	// ---- update ----
	virtual void update() = 0;
};

#endif
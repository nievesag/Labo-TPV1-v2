#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"

class Game;

class GameObject
{
	// atributos protegidos
protected:

	// puntero al game
	Game* game;

	// metodos publicos
public:

	GameObject();

	GameObject(Game* game)
		: game(game) {}

	// destructora virtual
	virtual ~GameObject();

	// ---- render ----
	virtual void render(SDL_Rect destRect) const = 0;

	// ---- update ----
	virtual void update() = 0;
};

#endif
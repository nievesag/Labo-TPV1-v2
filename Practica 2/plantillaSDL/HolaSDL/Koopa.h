#ifndef KOOPA_H
#define KOOPA_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>
#include "Collision.h"

#include "Enemy.h"

class Game;

using uint = unsigned int;
using namespace std;

class Koopa : public Enemy
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego


public:
	Koopa(Game* g, std::istream& in);

	// -- update --
	void update();

};

#endif
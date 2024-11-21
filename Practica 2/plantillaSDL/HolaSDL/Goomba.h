#ifndef GOOMBA_H
#define GOOMBA_H

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

class Goomba : public Enemy
{
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

public:
	Goomba(Game* g, Point2D<int> pos, Texture* t);

	// -- update --
	void update() override;


};

#endif
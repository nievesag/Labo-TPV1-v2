#pragma once
#include "checkML.h"

#include <string>
#include <vector>
#include "Texture.h"
#include "Game.h"

using namespace std;
using uint = unsigned int;

class Game;

// renderiza el mapa segun se mueve el personaje
class TileMap
{
private:
	Texture* texture;
	Game* game;

	vector<string> indices;
	int x, y;

public:
	TileMap();
	TileMap(Game* gameRef, vector<string> indice);
	~TileMap();

	void render();
	void update();

	//colisiones?
	void hit();

};

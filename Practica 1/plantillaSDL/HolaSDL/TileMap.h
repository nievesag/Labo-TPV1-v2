#pragma once
#include "checkML.h"

#include <string>
#include <vector>
#include "Texture.h"
#include "Game.h"
#include <iostream>
using namespace std;
using uint = unsigned int;

class Game;

// dibuja el fondo y los obstaculos segun avanza el personaje
class TileMap
{
private:
	Texture* texture = nullptr; // puntero a textura del array de textures
	Game* game = nullptr;
	Texture* background = nullptr; 

	vector<vector<int>> indices;
	int x, y;

public:
	TileMap();
	TileMap(Game* g, std::istream& in);
	~TileMap();

	void render();
	void update();
	void load(std::istream& file);

	// detecta colisiones
	void hit();

};
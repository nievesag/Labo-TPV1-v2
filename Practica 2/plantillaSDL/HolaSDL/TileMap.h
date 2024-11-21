#pragma once
#include "checkML.h"

#include <string>
#include <vector>
#include "Texture.h"
#include "Game.h"
#include <iostream>
#include "SceneObject.h"
using namespace std;
using uint = unsigned int;

class Game;

// dibuja el fondo y los obstaculos segun avanza el personaje
class TileMap : public SceneObject
{
private:

	Texture* texture = nullptr; // puntero a textura del array de textures
	//Game* game = nullptr;
	Texture* background = nullptr; 
	Point2D<int> pos = Point2D<int>(0, 0);
	vector<vector<int>> indices;
	int x, y;

public:
	//TileMap();
	TileMap(Game* g, std::istream& in, Point2D<int> position);
	~TileMap();

	void render() const override;
	void update() override;
	void load(std::istream& file);

	// detecta colisiones
	Collision hit(const SDL_Rect& rect, Collision::Target t);
};
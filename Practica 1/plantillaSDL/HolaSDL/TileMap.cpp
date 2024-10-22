#include "TileMap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

TileMap::TileMap(Game* gameRef, vector<string> indice)
{
	indices = indice;
	game = gameRef;
	texture = game->getTexture(Game::BACKGROUND);


}

void TileMap::render()
{
	for (int i = 0; i < indices.size(); i++) {

		if (indices[i] == "-1") {
			SDL_Rect destino{ x, y, texture->getFrameWidth(), texture->getFrameHeight() };
			texture->renderFrame(destino, 0, (abs(x) / FRAME_PERIOD) % texture->getNumColumns());
		}
	}


}
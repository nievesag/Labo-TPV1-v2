#include "TileMap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

TileMap::TileMap()
{

}

TileMap::TileMap(Game* g, vector<vector<int>> ind) : indices(ind), game(g), x(0), y(0)
{
	texture = game->getTexture(Game::BACKGROUND);
}

TileMap::~TileMap()
{

}

void TileMap::render()
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = mapOffset / TILE_SIDE;

	// Anchura oculta de esa primera columna, no se puede volver hacia atras
	int d0 = mapOffset % TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) 
	{
		for (int j = 0; j < WINDOW_HEIGHT; ++j) 
		{
			// Índice en el conjunto de patrones de la matriz de índices
			int indice = indices[x0 + i][j];

			// Separa número de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			background->renderFrame(rect, fx, fy);
		}
	}
}

void TileMap::update()
{

}

void TileMap::hit()
{

}

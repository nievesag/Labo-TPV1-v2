#include "TileMap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

TileMap::TileMap()
{

}

TileMap::TileMap(Game* g, std::istream& in) : game(g)
{
	load(in);
	texture = game->getTexture(Game::BACKGROUND);
}

TileMap::~TileMap()
{

}

void TileMap::load(std::istream& file)
{
	std::ifstream archivo("../assets/maps/world1.csv");
	if (!archivo.is_open()) {
		std::cerr << "Error al abrir el archivo" << std::endl;
		return;
	}

	std::string linea;
	while (std::getline(archivo, linea)) {
		std::vector<int> fila;
		std::stringstream ss(linea);
		std::string valor;

		while (std::getline(ss, valor, ',')) {
			fila.push_back(std::stoi(valor));
		}

		indices.push_back(fila);
	}

	archivo.close();
}

void TileMap::render()
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = game->getMapOffset() / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = game->getMapOffset() % TILE_SIDE;

	// tamaño del cuadro a pintarse
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) 
	{
		for (int j = 0; j < WINDOW_HEIGHT; ++j) 
		{
			// indice en el conjunto de patrones de la matriz de ?ndices
			int indice = indices[j][i + x0];

			// Separa numero de fila y de columna
			int fx = indice % 9;
			int fy = indice / 9;

			rect.x = -d0 + i * TILE_SIDE;
			rect.y = j * TILE_SIDE;

			// Usa renderFrame para pintar la tesela
			texture->renderFrame(rect, fy, fx);
		}
	}
}

void TileMap::update()
{

}

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer)
{
	Collision c;
	c.collides = false;
	c.damages = false;

	// Celda del nivel que contiene la esquina superior izquierda del rectángulo
	int row0 = rect.y / TILE_SIDE;
	int col0 = rect.x / TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rectángulo
	int row1 = (rect.y + rect.h) / TILE_SIDE;
	int col1 = (rect.x + rect.w) / TILE_SIDE;

	for (int row = row0; row <= row1; ++row)
	{
		for (int col = col0; col <= col1; ++col)
		{
			if (indices[row][col] % texture->getNumColumns() < OBSTACLE_THRESHOLD) {
				SDL_Rect rectTile;
				rectTile.w = texture->getFrameWidth();
				rectTile.h = texture->getFrameHeight();
				rectTile.x = row * TILE_SIDE;
				rectTile.y = col * TILE_SIDE;

				c.collides = SDL_IntersectRect(&rectTile, &rect, &c.intersection);
				return c;
				
			}
				
		}
	}

	return c;
}
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
			// ?ndice en el conjunto de patrones de la matriz de ?ndices
			int indice = indices[j][i + x0];

			// Separa n?mero de fila y de columna
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

void TileMap::hit()
{

}
#include "TileMap.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

TileMap::TileMap()
{

}

TileMap::TileMap(Game* g, std::string in) : game(g)
{
	load(in);
}

TileMap::~TileMap()
{

}

void TileMap::load(std::string file)
{
	ifstream fichero;
	fichero.open(file);
	if (!fichero.is_open()) 
	{
		throw string("fichero de mapa no encontrado");
	}
	else {
		string line;
		vector<int> fila;

		while (getline(fichero, line))
		{
			std::istringstream stream(line);
			string num;

			while (getline(stream, num, ','))
			{
				std::istringstream convertir(num); // construye flujo temporal istringstream
				int n;
				convertir >> n; // el flujo convierte a int desde lectura
				fila.push_back(n); // mete n a fila
			}

			indices.push_back(fila); // mete fila a la matriz
		}
	}

	fichero.close();
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
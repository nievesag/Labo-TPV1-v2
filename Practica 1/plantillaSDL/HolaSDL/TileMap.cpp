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

	// tama�o del cuadro a pintarse
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

Collision TileMap::hit(const SDL_Rect& rect, bool fromPlayer) {
	
	Collision collision; // Inicializa una instancia de Collision

	// Calcula las celdas del nivel que contienen las esquinas del rect�ngulo
	// Celda del nivel que contiene la esquina superior izquierda del rect�ngulo
	int row0 = rect.y / TILE_SIDE;
	int col0 = rect.x / TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rect�ngulo
	int row1 = (rect.y + rect.h - 1) / TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / TILE_SIDE;

	for (int row = row0; row <= row1; ++row) 
	{
		for (int col = col0; col <= col1; ++col) 
		{
			int index = indices[row][col];

			// Verifica si hay colisi�n con un obst�culo 
			if (index != -1 && index % texture->getNumColumns() < OBSTACLE_THRESHOLD) // ESTO CONFIRMA COLISION
			{
				collision.collides = true;

				// Calcula la intersecci�n entre rect y el tile en cuesti�n
				SDL_Rect tileRect = { col * TILE_SIDE, row * TILE_SIDE, TILE_SIDE, TILE_SIDE };
				SDL_IntersectRect(&rect, &tileRect, &collision.intersection);

				// Aqu� puedes asignar el puntero `collider` y establecer `damages` si aplica
				collision.collider = nullptr; // Ajusta esto seg�n tu implementaci�n
				collision.damages = fromPlayer; // Ejemplo: tal vez solo da�a si es el jugador

				//std::cout << collision.collides << endl;
				return collision;
			}
		}
	}

	return collision; // Retorna la instancia sin colisi�n si no encontr� obst�culos
	
}

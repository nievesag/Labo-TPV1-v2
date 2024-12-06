#include "TileMap.h"
#include "PlayState.h"

// Velocidad y frecuencia de cambio de frame
constexpr int SPEED = 10;
constexpr int FRAME_PERIOD = 20;

TileMap::TileMap(Game* g, std::istream& in, Point2D<int> p, Texture* t, PlayState* play)
	: SceneObject(g, p, t, play)
{
	load(in);
}

TileMap::~TileMap()
{

}

void TileMap::load(std::istream& file)
{
	std::ifstream archivo("../assets/maps/world" + to_string(game->getCurrentLevel()) + ".csv");
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

void TileMap::render() const
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = playState->getMapOffset() / TILE_SIDE;
	// Anchura oculta de esa primera columna
	int d0 = playState->getMapOffset() % TILE_SIDE;

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

void TileMap::update() { }

Collision TileMap::hit(const SDL_Rect& rect, Collision::Target t) {
	
	Collision c; // Inicializa una instancia de Collision

	// Calcula las celdas del nivel que contienen las esquinas del rect�ngulo
	// Celda del nivel que contiene la esquina superior izquierda del rect�ngulo
	int row0 = rect.y / TILE_SIDE;
	int col0 = rect.x / TILE_SIDE;

	// Celda del nivel que contiene la esquina inferior derecha del rect�ngulo
	int row1 = (rect.y + rect.h - 1) / TILE_SIDE;
	int col1 = (rect.x + rect.w - 1) / TILE_SIDE;

	//ajuste para que no pete
	row0 = max(0, row0);
	row1 = min(static_cast<int>(indices.size()) - 1, row1);
	col0 = max(0, col0);
	col1 = min(static_cast<int>(indices[0].size()) - 1, col1);

	for (int row = row0; row <= row1; ++row) 
	{
		for (int col = col0; col <= col1; ++col) 
		{
			int index = indices[row][col];

			// Verifica si hay colisi�n con un obst�culo 
			if (index != -1 && index % texture->getNumColumns() < OBSTACLE_THRESHOLD) // ESTO CONFIRMA COLISION
			{
				//cout << "col";
				SDL_Rect auxRect{
					col * TILE_SIDE,
					row * TILE_SIDE,
					TILE_SIDE,
					TILE_SIDE
				};

				// Calculamos la interseccion
				if (SDL_IntersectRect(&rect, &auxRect, &c.intersectionRect))
				{
					c.result = Collision::OBSTACLE; // el resultado sera obstacle porque el tilemap no hace damage
					c.horizontal = c.intersectionRect.w;
					c.vertical = c.intersectionRect.h;
					return c;
				}
			}
		}
	}

	return c; // Retorna la instancia sin colisi�n si no encontr� obst�culos
}

void TileMap::manageCollisions(Collision c)
{
}

SceneObject* TileMap::clone() const
{
	return new TileMap(*this);
}
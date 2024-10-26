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
	texture = game->getTexture(Game::BACKGROUND);
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

	/*	for (const auto& row : indices) {
			for (const auto& value : row) {
				std::cout << value << " ";
			}
			std::cout << std::endl;
		}*/
	}

	fichero.close();

	//while (fichero) {
	//	int c = 0;
	//	char cAux = ','; // Se separa el archivo por comas.
	//	std::vector<int> fila;

	//	// Mientras cAux siga obteniendo ","... (lee la fila).
	//	while (cAux == ',') {
	//		// Lee el entero y lo añade a la fila actual.
	//		fichero >> c;
	//		fila.push_back(c);

	//		// Get() lee el siguiente char (",").
	//		cAux = fichero.get();
	//	}
	//	indices.push_back(fila);

	//	
	//}


}

void TileMap::render()
{
	// Primera columna de la matriz del mapa visible en la ventana
	int x0 = game->getMapOffset() / TILE_SIDE;

	// Anchura oculta de esa primera columna, no se puede volver hacia atras
	int d0 = game->getMapOffset() % TILE_SIDE;

	// Recuadro donde se pintará la tesela en la ventana
	SDL_Rect rect;
	rect.w = TILE_SIDE;
	rect.h = TILE_SIDE;

	// Pintamos los WINDOW_WIDTH + 1 (aunque se salga) x WINDOW_HEIGHT recuadros del mapa
	for (int i = 0; i < WINDOW_WIDTH + 1; ++i) 
	{
		for (int j = 0; j < WINDOW_HEIGHT; ++j)
		{
			
			if (x0 + i < indices.size() && j < indices[0].size()) {
				// Índice en el conjunto de patrones de la matriz de índices
				int indice = indices[x0 + i][j];

			
				// ?ndice en el conjunto de patrones de la matriz de ?ndices

				// Separa n?mero de fila y de columna
				int fx = indice / 9;
				int fy = indice % 9;

				rect.x = -d0 + j * TILE_SIDE;
				rect.y = i * TILE_SIDE;

				cout << "mmmmm";
				// Usa renderFrame para pintar la tesela
				texture->renderFrame(rect, fx, fy);
		}
		}
	}
}

void TileMap::update()
{
	render();
}

void TileMap::hit()
{

}
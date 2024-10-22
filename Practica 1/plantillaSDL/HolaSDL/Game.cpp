#include "Game.h"

#include <string>
#include <iostream>
#include <istream>
#include "TileMap.h"

using namespace std;

// Formato de la especificacion de una textura
struct TextureSpec
{
	const char* route;	// Ruta del archivo
	uint numColumns;	// num de frames por fila, nw
	uint numRows;		// num de frames por columna, nh
};

// directorio raiz de los archivos de textura
const string textureRoot = "../assets/imgs/";

// especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 12, 1},
};

Game::Game() : randomGenerator(time(nullptr)), exit(false)
{
	int winX, winY; // Posición de la ventana
	winX = winY = SDL_WINDOWPOS_CENTERED;

	// Inicialización del sistema, ventana y renderer
	SDL_Init(SDL_INIT_EVERYTHING);

	// ERRORES DE SDL
	try 
	{
		// crea la ventana
		window = SDL_CreateWindow("Super Mario", winX, winY, WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN);

		// crea el renderer para la ventana
		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

		if (window == nullptr || renderer == nullptr)
			throw "Error cargando ventana de juego o renderer"s;
	}
	catch (...) 
	{
		std::cout << "Error cargando ventana de juego o renderer";
		EndGame();
	}

	init();
}

Game::~Game()
{
	// Elimina los objetos del juego
	

	// Elimina las texturas
	for (Texture* texture : textures) delete texture;

	// Desactiva la SDL
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// ----- LOGICA DE JUEGO -----
// cargar | manejar eventos -> actualizar -> pintar -> manejar eventos etc

void Game::init()
{
	loadTextures();
	loadMap("../assets/maps/world1.csv");
	loadObjectMap("../assets/maps/world1.txt");
}

// CARGA
void Game::loadTextures()
{
	try {
		// bucle para rellenar el array de texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {

			// crea la textura con el url, width y height
			Texture* tex = new Texture(renderer, 
												(textureRoot + textureSpec[i].route).c_str(), 
												textureSpec[i].numRows, 
												textureSpec[i].numColumns);

			// la mete en el array
			textures[i] = tex;

			if (textures[i] == nullptr) 
			{
				std::cout << "Textura null";
			}
		}
	}
	catch (...) {
		cout << "Textura no encontrada";
		EndGame();
	}
}

void Game::loadMap(std::string file)
{
	ifstream fichero;
	fichero.open(file);
	if (!fichero.is_open()) {
		throw string("fichero de mapa no encontrado");
	}
	else {
		string line;
		vector<int> fila;
		vector<vector<int>> matriz;

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

			matriz.push_back(fila); // mete fila a la matriz

			// Imprimir los valores de la fila
			//for (const auto& elemento : fila) {
			//	std::cout << elemento << " ";
			//}
			//std::cout << std::endl;
		}

		tilemap = new TileMap(this, matriz);
	}

	fichero.close();
}

void Game::loadObjectMap(const char* mapa)
{
	// Carga el mapa
	istream file(mapa);

	// Leemos el mapa linea a linea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;
	getline(file, line);

	while (!file) 
	{
		// Usamos un stringstream para leer la linea como si fuera un flujo
		stringstream lineStream(line);

		char tipo;
		lineStream >> tipo;

		switch (tipo) {
		case 'M':
			player = new Player(this, lineStream);
			break;
		case 'G':
			break;
		case 'B':
			break;
		}

	}
}

// RUN
void Game::run()
{
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit)
	{
		handleEvents();

		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BT_FRAMES) {
			update(); // actualiza todos los objetos de juego
			startTime = SDL_GetTicks();
		}
		render(); // renderiza todos los objetos de juego
	}
}

// ACTUALIZAR
void Game::update()
{
	
}

// PINTAR
void Game::render() const
{
	
}

// MANEJAR EVENTOS
void Game::handleEvents()
{
	SDL_Event event; // crea evento

	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {

		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		//else { player->handleEvents(event); }
	}
}

// MANEJO DE COLISONES
void Game::collides()
{
	
}

void Game::EndGame()
{
	exit = true;
}

void Game::playerLives()
{
	//cout << "VIDAS RESTANTES: " <<  << endl;
}
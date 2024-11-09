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
	{"supermario.png", 22, 1},
	{"blocks.png", 6, 1},
	{"mushroom.png", 1, 1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1}
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
	delete player;

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

	// TILEMAP
	std::ifstream tiles("../assets/maps/world1.csv");
	// control de errores
	if (!tiles.is_open()) 
	{
		std::cout << "Error cargando el tilemap";
	}
	tilemap = new TileMap(this, tiles);
	tiles.close();

	// MAPA
	std::ifstream mapa("../assets/maps/world1.txt");
	// control de errores
	if (!mapa.is_open())
	{
		std::cout << "Error cargando el mapa";
	}
	loadObjectMap(mapa);
	mapa.close();
}

// CARGA
void Game::loadTextures()
{
	try {
		// bucle para rellenar el array de texturas
		for (int i = 0; i < NUM_TEXTURES; i++) {

			// crea la textura con el url, width y height
			textures[i] = new Texture(renderer,
									(textureRoot + textureSpec[i].route).c_str(), 
									textureSpec[i].numRows, 
									textureSpec[i].numColumns);


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

void Game::loadObjectMap(std::ifstream& mapa)
{
	// Leemos el mapa linea a linea para evitar acarreo de errores
	// y permitir extensiones del formato
	string line;
	getline(mapa, line);

	while (mapa) 
	{
		// Usamos un stringstream para leer la linea como si fuera un flujo
		stringstream lineStream(line);

		char tipoL;
		lineStream >> tipoL;

		switch (tipoL) {
		case 'M':
			player = new Player(this, lineStream);
			break;
		case 'G':
			 goomba = new Goomba(this, lineStream);
			 goombaVec.push_back(goomba);
			break;
		case 'B':
			block = new Block(this, lineStream);
			blockVec.push_back(block);
			break;
		}

		getline(mapa, line);
	}
}

// RUN
void Game::run()
{
	// get ticks al inicio del bucle
	startTime = SDL_GetTicks();

	while (!exit)
	{
		update(); // actualiza todos los objetos de juego
		render(); // renderiza todos los objetos de juego
		handleEvents();

		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime > TIME_BT_FRAMES) 
		{
			startTime = SDL_GetTicks();
		}
	}
}

// ACTUALIZAR
void Game::update()
{
	tilemap->update();

	player->update();

	for (int i = 0; i < goombaVec.size(); i++) 
	{
		goombaVec[i]->update();
	}

	for (int i = 0; i < blockVec.size(); i++)
	{
		blockVec[i]->update();
		//cout << "hola" << endl;
	}
}

// PINTAR
void Game::render() const
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	//Fondo azul
	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);

	// render mapa
	tilemap->render();

	// render mario
	player->render();

	// render goombas
	for (int i = 0; i < goombaVec.size(); i++)
	{
		goombaVec[i]->render();
	}

	// render blocks
	for (int i = 0; i < blockVec.size(); i++)
	{
		blockVec[i]->render();
	}

	// presenta la escena en pantalla
	SDL_RenderPresent(renderer);
}

// MANEJAR EVENTOS
void Game::handleEvents()
{
	SDL_Event event; // crea evento

	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) 
	{
		// si se solicita quit bool exit = true
		if (event.type == SDL_QUIT) EndGame();

		// MANEJO DE EVENTOS DE OBJETOS DE JUEGO
		else { player->handleEvents(event); }
	}
}

// MANEJO DE COLISONES
// Recibe el SDL_Rect del objeto que se va a mover y quiere comprobar las colisiones.
// Game tiene acceso a todos los objetos del juego,
// puede preguntarle a cada uno de ellos (con el metodo hit) si colisiona con el rect
Collision Game::checkCollisions(const SDL_Rect& rect, bool fromPlayer)
{
	// itera sobre los objeto del juego llamando a sus hit
	// si alguno devuelve que ha habido colision, interrumpe la busqueda y devuelve ese resultado.

	Collision c;

	Collision colTilemap = tilemap->hit(rect, fromPlayer); 

	if (colTilemap.collides) {
		return colTilemap;
	}


	// hit mario
	player->hit(rect, true);

	// hit goombass
	for(int i = 0; i < goombaVec.size(); i++)
	{
		goombaVec[i]->hit(rect, true);
	}

	// hit blocks
	for(int i = 0; i < blockVec.size(); i++)
	{
		blockVec[i]->hit(rect, true);
	}

	return c;
}

void Game::EndGame()
{
	exit = true;
}

void Game::playerLives()
{
	//cout << "VIDAS RESTANTES: " <<  << endl;
}


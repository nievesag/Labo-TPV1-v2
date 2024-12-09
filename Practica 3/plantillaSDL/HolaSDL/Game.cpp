#include "Game.h"

#include <string>
#include <iostream>
#include <istream>

#include "MainMenuState.h"
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
const string textureRoot = "../assets/images/";

// especificacion de las texturas del juego
const array<TextureSpec, Game::NUM_TEXTURES> textureSpec{
	TextureSpec{"background.png", 9, 7},
	{"mario.png", 12, 1},
	{"supermario.png", 22, 1},
	{"blocks.png", 6, 1},
	{"mushroom.png", 1, 1},
	{"goomba.png", 3, 1},
	{"koopa.png", 4, 1},
	{"coin.png", 4, 1},
	{"lift.png", 1, 1},
	{"portada.png", 1, 1},
	{"continuar.png", 1, 1},
	{"salir.png", 1, 1},
	{"numbers.png", 10, 1},
	{"volver.png", 1, 1},
	{"nombreMario.png", 5, 1},
	{"nivel1.png", 1, 1},
	{"nivel2.png", 1, 1},
	{"piranha.png", 2, 1},
	{"plant.png", 4, 1},
	{"gameOver.png", 1, 1},
	{"hasGanado.png", 1, 1},
	{"shell.png", 2, 1},
	{"star.png", 4, 1},
	{"firemario.png", 21, 1}
};

Game::Game() : exit(false)
{
	maxWorlds = 3;
	currentWorld = 1;
	marioState = 0;

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
		setExit(true);
	}

	init();
}

Game::~Game()
{
	delete gsMachine;

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
	// texturas
	loadTextures();

	// maquina de estados
	gsMachine = new GameStateMachine();
	GameState* mms = new MainMenuState(this);
	gsMachine->pushState(mms);
}

// CARGA
void Game::loadTextures()
{
	try {
		// bucle para rellenar el array de texturas
		for (int i = 0; i < NUM_TEXTURES; ++i) {

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
		setExit(true);
	}
}

void Game::playerLives()
{
}

// RUN
void Game::run()
{
	while (!exit)
	{
		handleEvents();
		// get ticks al inicio del bucle
		startTime = SDL_GetTicks();
		
		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - startTime;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAMERATE)
		{
			update(); // actualiza todos los objetos de juego
			SDL_Delay(FRAMERATE - elapsed);
		}

		render(); // renderiza todos los objetos de juego
	}

	//deleteEntities();
}

// ACTUALIZAR
void Game::update()
{
	gsMachine->update();
}

void Game::handleEvents()
{
	// MIENTRAS HAYA EVENTOS
		// si hay eventos &event se llena con el evento a ejecutar si no NULL
		// es decir, pollea hasta que se hayan manejado todos los eventos
	while (SDL_PollEvent(&event) && !exit) {
		if (event.type == SDL_QUIT)
			exit = true;
		else {
			gsMachine->handleEvent(event);
		}
	}
}

// PINTAR
void Game::render() 
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	gsMachine->render();

	// presenta la escena en pantalla
	SDL_RenderPresent(renderer);
}
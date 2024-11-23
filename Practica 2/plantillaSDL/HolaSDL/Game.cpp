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
const string textureRoot = "../assets/images/";

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

	Point2D<double> pos = Point2D<double>(0, 0);
	SceneObject* tilemap = new TileMap(this, tiles, pos);
	gameList.push_back(tilemap);
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
		Point2D<double> pos;

		char tipoL;
		lineStream >> tipoL;

		if(tipoL == 'M')
		{
			int lives;

			lineStream >> pos;
			pos = pos - Point2D<double>(0, 1);

			lineStream >> lives;
			 player = new Player(this, pos, getTexture(MARIO), lives);

			gameList.push_back(player);
		}
		else if(tipoL == 'G')
		{
			lineStream >> pos;
			pos = pos - Point2D<double>(0, 1);

			SceneObject* goomba = new Enemy(this, pos, getTexture(GOOMBA));
			gameList.push_back(goomba);
		}
		else if (tipoL == 'B')
		{
			char tipoL;
			char accionL;

			lineStream >> pos;
			pos = pos - Point2D<double>(0, 1);

			lineStream >> tipoL;
			lineStream >> accionL;

			SceneObject* block = new Block(this, pos, getTexture(BLOCK), tipoL, accionL);

			gameList.push_back(block);
		}
		else if(tipoL == 'K')
		{
			lineStream >> pos;
			pos = pos - Point2D<double>(0, 1);

			SceneObject* koopa = new Enemy(this, pos, getTexture(KOOPA));
			gameList.push_back(koopa);
		}

		getline(mapa, line);
	}
}

// RUN
void Game::run()
{
	while (!exit)
	{
		// get ticks al inicio del bucle
		startTime = SDL_GetTicks();

		update(); // actualiza todos los objetos de juego
		render(); // renderiza todos los objetos de juego
		handleEvents();

		// tiempo desde ultima actualizacion
		frameTime = SDL_GetTicks() - startTime;

		if (frameTime < TIME_BT_FRAMES) 
		{
			SDL_Delay(TIME_BT_FRAMES - frameTime);
		}
	}
}

// ACTUALIZAR
void Game::update()
{
	for (auto obj : gameList) {
		obj->update();
	}

	updateEntities();

	// si muere el player acaba el juego
	//if (!player->getAlive()) EndGame();
}

void Game::updateEntities()
{
	/*
	for (SceneObject* obj : gameList) {
		if(!obj->getAlive())
		{
			delete obj;
			gameList.erase();
		}
	}

	// GOOMBAS
	for (int i = 0; i < goombaVec.size(); i++) 
	{
		if (!goombaVec[i]->getAlive())
		{
			delete goombaVec[i];

			// lo quita del vector
			goombaVec.erase(goombaVec.begin() + i);
		}
	}

	// BLOQUES
	for (int i = 0; i < blockVec.size(); i++)
	{
		if (!blockVec[i]->getAlive() && (blockVec[i]->getTipo() == 0))
		{
			delete blockVec[i];

			// lo quita del vector
			blockVec.erase(blockVec.begin() + i);
		}
	}

	// SETAS
	for (int i = 0; i < setaVec.size(); i++)
	{
		if (!setaVec[i]->getAlive())
		{
			delete setaVec[i];

			// lo quita del vector
			setaVec.erase(setaVec.begin() + i);
		}
	}

	// KOOPAS
	for (int i = 0; i < koopaVec.size(); i++)
	{
		if (!koopaVec[i]->getAlive())
		{
			delete koopaVec[i];

			// lo quita del vector
			koopaVec.erase(koopaVec.begin() + i);
		}
	}
	*/
}

// PINTAR
void Game::render() const
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	//Fondo azul
	SDL_SetRenderDrawColor(renderer, 138, 132, 255, 255);

	for (auto obj : gameList) {
		obj->render();
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
Collision Game::checkCollisions(const SDL_Rect& rect, Collision::Target target)
{
	Collision result;

	for (auto obj : gameList)
	{
		if(obj->hit(rect, target).result != Collision::NONE)
		{
			result = obj->hit(rect, target);
			return result;
		}
	}

	return result;
}

void Game::EndGame()
{
	exit = true;
}

void Game::playerLives()
{
	//cout << "VIDAS RESTANTES: " <<  << endl;
}
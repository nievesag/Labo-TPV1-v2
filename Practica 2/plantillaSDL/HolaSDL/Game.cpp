#include "Game.h"

#include <string>
#include <iostream>
#include <istream>

#include "Coin.h"
#include "Lift.h"
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
	{"lift.png", 1, 1}
};

Game::Game() : randomGenerator(time(nullptr)), exit(false)
{
	nextObject = 0;
	currentWorld = 1;

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

	loadLevel(to_string(currentWorld - '0'), "../assets/maps/world");
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

	int i = 0;
	while (mapa) 
	{
		// Usamos un stringstream para leer la linea como si fuera un flujo
		stringstream lineStream(line);

		if(i == 0)
		{
			lineStream >> r >> g >> b;
		}

		Point2D<int> pos;

		char tipoL;
		lineStream >> tipoL;

		if(tipoL == 'M')
		{
			int lives;

			lineStream >> pos;
			
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			lineStream >> lives;
			player = new Player(this, pos, getTexture(MARIO), lives);

			objectQueue.push_back(player);
		}
		else if(tipoL == 'G')
		{
			lineStream >> pos;

			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			SceneObject* goomba = new Goomba(this, pos, getTexture(GOOMBA));

			objectQueue.push_back(goomba);
		}
		else if (tipoL == 'B')
		{
			char tipoL;
			char accionL;

			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);
		

			lineStream >> tipoL;
			lineStream >> accionL;

			SceneObject* block = new Block(this, pos, getTexture(BLOCK), tipoL, accionL);

			objectQueue.push_back(block);
		}
		else if(tipoL == 'K')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - (TILE_SIDE * 2));
		
			SceneObject* koopa = new Koopa(this, pos, getTexture(KOOPA));
			objectQueue.push_back(koopa);

		}
		else if (tipoL == 'L')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);
			

			Vector2D<int> speed;
			double x = 0;
			double y = 0;
			lineStream >> y;
			speed.setY(y);

			SceneObject* lift = new Lift(this, pos, getTexture(LIFT), speed);
			objectQueue.push_back(lift);
		}
		else if (tipoL == 'C')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);
		

			Pickable* coin = new Coin(this, pos, getTexture(COIN));
			objectQueue.push_back(coin);
		}
		else if (tipoL == 'P')
		{

		}
		else if(tipoL == 'X')
		{
			
		}

		getline(mapa, line);
		
		i++;
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
		// Tiempo que se ha tardado en ejecutar lo anterior
		uint32_t elapsed = SDL_GetTicks() - startTime;

		// Duerme el resto de la duraci�n del frame
		if (elapsed < FRAMERATE)
			SDL_Delay(FRAMERATE - elapsed);
	}
}

// ACTUALIZAR
void Game::update()
{
	addVisibleEntities();

	for (auto obj : gameList) {
		obj->update();
	}

	deleteEntities();

	// si muere el player acaba el juego
	//if (!player->getAlive()) EndGame();
}

void Game::deleteEntities()
{
	//for (SceneObject* obj : gameList) {
	//	if(!obj->getAlive())
	//	{
	//		delete obj;
	//		gameList.erase();
	//	}
	//}
}

// PINTAR
void Game::render() 
{
	// limpia pantalla
	SDL_RenderClear(renderer);

	// Fondo azul
	SDL_SetRenderDrawColor(renderer, r, g, b, 255);

	for (auto obj : gameList) {
		obj->render();
	}

	// presenta la escena en pantalla
	SDL_RenderPresent(renderer);
}

void Game::addVisibleEntities()
{
	// Borde derecho del mapa (+ una casilla)
	const int rightThreshold = mapOffset + WINDOW_WIDTH + TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getPosition().getX() < rightThreshold)
		addObject(objectQueue[nextObject++]->clone());
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
		else { player->handleEvent(event); }
	}
}

void Game::addObject(SceneObject* o)
{
	if(nextObject == 1)
	{
		gameList.push_front(o);
	}
	else
	{
		gameList.push_back(o);
	}
	nextObject++;
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

void Game::loadLevel(const string& file, const string& root)
{
	// TILEMAP
	// ifstream in(root + file + ".txt");
	// "../assets/maps/world" +
	// "to_string(k - '0')" + -> siendo k el mundo en el que estes
	// ".csv"
	//std::ifstream tiles(root + file + ".csv");
	std::ifstream tiles("../assets/maps/world1.csv");

	// control de errores
	if (!tiles.is_open())
	{
		std::cout << "Error cargando el tilemap";
	}

	Point2D<int> pos = Point2D<int>(0, 0);
	SceneObject* tilemap = new TileMap(this, tiles, pos, getTexture(BACKGROUND));
	objectQueue.push_back(tilemap);
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

void Game::playerLives()
{
	//cout << "VIDAS RESTANTES: " <<  << endl;
}
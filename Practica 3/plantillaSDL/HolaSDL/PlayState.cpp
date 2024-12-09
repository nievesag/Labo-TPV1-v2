#include "PlayState.h"
#include "TileMap.h"

#include <iostream>

#include "Coin.h"
#include "EndState.h"
#include "Lift.h"
#include "PauseState.h"
#include "Player.h"

PlayState::PlayState(Game* g, const std::string& file, const std::string& root)
	: GameState(g)
{
	endVictory = false;
	nextObject = 0;
	mapOffset = 0;
	int k = std::stoi(file);
	game->setCurrentLevel(k);
	loadLevel(file, root);

	infobar = new InfoBar(game, this);
	stateList.push_back(infobar);
	
}

void PlayState::loadObjectMap(std::ifstream& mapa)
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

		if (i == 0)
		{
			lineStream >> r >> g >> b;
		}

		Point2D<int> pos;

		char tipoL;
		lineStream >> tipoL;

		if (tipoL == 'M' && !falled)
		{
			int lives;
			cout << falled << endl;
			lineStream >> pos;

			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			lineStream >> lives;

			if (player == nullptr)
			{
				cout << "hola" << endl;
				/*pos.setX(6100);
				setMapOffset(6100);*/
				player = new Player(game, pos, game->getTexture(Game::MARIO), lives, Vector2D<int>(0, 0), this);
				//objectQueue.push_back(player);
				//addObject(player);
				stateList.push_back(player);
				gameList.push_back(player);
			}
			else
			{
				player->resetPosition(pos);

			}
			
		}
		else if (tipoL == 'G')
		{
			lineStream >> pos;

			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			SceneObject* goomba = new Goomba(game, pos, game->getTexture(Game::GOOMBA), Vector2D<int>(-7, 0), this);
			objectQueue.push_back(goomba);
			//addObject(goomba);
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

			SceneObject* block = new Block(game, pos, game->getTexture(Game::BLOCK), tipoL, accionL, this);
			objectQueue.push_back(block);
			//addObject(block);
		}
		else if (tipoL == 'K')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - (TILE_SIDE * 2));

			SceneObject* koopa = new Koopa(game, pos, game->getTexture(Game::KOOPA), Vector2D<int>(-7, 0), this);
			objectQueue.push_back(koopa);
			//addObject(koopa);
			
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

			SceneObject* lift = new Lift(game, pos,game->getTexture(Game::LIFT), speed, this);
			objectQueue.push_back(lift);
		}
		else if (tipoL == 'C')
		{
			lineStream >> pos;
			pos.setX(pos.getX() * TILE_SIDE);
			pos.setY(pos.getY() * TILE_SIDE - TILE_SIDE);

			Pickable* coin = new Coin(game, pos, game->getTexture(Game::COIN), this);
			objectQueue.push_back(coin);
			//addObject(coin);
		}
		else if (tipoL == 'P')
		{

		}
		else if (tipoL == 'X')
		{

		}

		getline(mapa, line);

		i++;
	}
}

void PlayState::update()
{
	addVisibleEntities();

	GameState::update();

	// si muere el player acaba el juego
	//if (!player->getAlive()) EndGame();

	if (endVictory || (player->getLives() <= 0))
	{
		// finaliza el juego
		// (aniade el estado de fin a la maquina de estados de application)
		game->getgsMachine()->pushState(new EndState(game, endVictory));
	}
}

void PlayState::deleteEntities()
{
	// si se ha perdido
	if (exit)
	{
		for (auto obj : objectQueue)
		{
			delete obj;
		}
	}
}

void PlayState::createSeta(Point2D<int> p)
{
	p.setY(p.getY() - TILE_SIDE);

	SceneObject* seta = new Mushroom(game, p, game->getTexture(Game::MUSHROOM), this);

	//objectQueue.push_back(seta);
	gameList.push_back(seta);
	stateList.push_back(seta);
}

void PlayState::render() const
{
	// Fondo azul
	SDL_SetRenderDrawColor(game->getRenderer(), r, g, b, 255);

	GameState::render();

	//cout << mapOffset << endl;

	//for (auto e : gameList) e->render();
}

void PlayState::reloadWorld(const string& file, const string& root)
{
	// todos los objetos del juego (salvo el jugador y el tilemap) han de ser destruidos y reemplazados
	for (auto e : gameList)
	{
		if (e != player)
		{
			delete e;
		}
	}

	setMapOffset(0);
	nextObject = 0;

	// TILEMAP
	// ifstream in(root + file + ".txt");
	// "../assets/maps/world" +
	// "to_string(k - '0')" + -> siendo k el mundo en el que estes
	// ".csv"
	std::ifstream tiles(root + file + ".csv");
	//std::ifstream tiles("../assets/maps/world1.csv");
	std::cout << root + file + ".csv" << std::endl;
	// control de errores
	if (!tiles.is_open())
	{
		std::cout << "Error cargando el tilemap";
	}

	Point2D<int> pos = Point2D<int>(0, 0);
	tilemap = new TileMap(game, tiles, pos, game->getTexture(Game::BACKGROUND), this);
	gameList.push_front(tilemap);
	stateList.push_front(tilemap);
	tiles.close();

	// MAPA
	std::ifstream mapa(root + file + ".txt");
	// control de errores
	if (!mapa.is_open())
	{
		std::cout << "Error cargando el mapa";
	}
	loadObjectMap(mapa);

	mapa.close();
}
void PlayState::addVisibleEntities()
{
	// Borde derecho del mapa (+ una casilla)
	const int rightThreshold = mapOffset + Game::WIN_WIDTH + TILE_SIDE;

	while (nextObject < objectQueue.size() && objectQueue[nextObject]->getPosition().getX() < rightThreshold)
	{
		addObject(objectQueue[nextObject++]->clone());
	}
}

void PlayState::addObject(SceneObject* o)
{
	
		gameList.push_back(o);
		stateList.push_back(o);
	
	
}

// MANEJO DE COLISONES
// Recibe el SDL_Rect del objeto que se va a mover y quiere comprobar las colisiones.
// Game tiene acceso a todos los objetos del juego,
// puede preguntarle a cada uno de ellos (con el metodo hit) si colisiona con el rect
Collision PlayState::checkCollisions(const SDL_Rect& rect, Collision::Target target)
{
	Collision result;

	for (auto obj : gameList)
	{
		result = obj->hit(rect, target);

		if (result.result != Collision::NONE)
		{
			return result;
		}
	}

	return result;
}

void PlayState::handleEvent(const SDL_Event& event)
{
	GameState::handleEvent(event);

	// si se pulsa esc
	if (event.type == SDL_KEYDOWN && event.key.keysym.scancode == SDL_SCANCODE_E) {

		// pausa el juego
		// (aniade el estado de pausa a la maquina de estados de application)
		game->getgsMachine()->pushState(new PauseState(game, this));
	}
}

void PlayState::loadLevel(const string& file, const string& root)
{
	// TILEMAP
	// ifstream in(root + file + ".txt");
	// "../assets/maps/world" +
	// "to_string(k - '0')" + -> siendo k el mundo en el que estes
	// ".csv"
	std::ifstream tiles(root + file + ".csv");
	//std::ifstream tiles("../assets/maps/world1.csv");
	cout << root + file + ".csv" << endl;
	// control de errores
	if (!tiles.is_open())
	{
		std::cout << "Error cargando el tilemap";
	}

	Point2D<int> pos = Point2D<int>(0, 0);
	tilemap = new TileMap(game, tiles, pos, game->getTexture(Game::BACKGROUND), this);
	//objectQueue.push_front(tilemap);
	//addObject(tilemap);
	gameList.push_front(tilemap);

	stateList.push_front(tilemap);
	tiles.close();

	// MAPA
	std::ifstream mapa(root + file + ".txt");
	// control de errores
	if (!mapa.is_open())
	{
		std::cout << "Error cargando el mapa";
	}
	loadObjectMap(mapa);

	mapa.close();
	
}

void PlayState::playerLives()
{
	//cout << "VIDAS RESTANTES: " <<  << endl;
}
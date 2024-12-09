#ifndef GAME_H
#define GAME_H

// Biblioteca estándar de C++
#include <array>

// Biblioteca SDL
#include <SDL.h>

// Nuestras clases
#include "Texture.h"

// MEMORY LEAKS
#include "checkML.h"

// SDL
#include <SDL.h>
#include "SDL_image.h"

// AUX
#include <array>
#include <vector>
#include <fstream>
#include <random>
#include <time.h>
#include <string>
#include <sstream>
	// classes
#include "Texture.h"
#include "Vector2D.h"
#include "Collision.h"
#include "GameStateMachine.h"
class TileMap;

// GAME OBJECTS
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Koopa.h"

using uint = unsigned int;

// gestion de frames y framerate 
static constexpr double
					FRAMERATE = 50,						// frames por segundo
					TIME_BT_FRAMES = 1 / FRAMERATE,		// tiempo entre frames
					MARIO_SPEED = 0.0009,	// velocidad de mario
					ENEMY_SPEED = 0.0003,	// velocidad de goombas
					SPEED_LIMIT = 10,
					MOVE_PERIOD = 5;
					
					

// constantes estaticas en Game
// -- para render de tilemap
constexpr int TILE_SIDE = 32;  
constexpr int WINDOW_WIDTH = 18;
constexpr int WINDOW_HEIGHT = 16;
constexpr int OBSTACLE_THRESHOLD = 4; // constante
constexpr int MAP_MAX_OFFSET = 6100;
constexpr int GRAVITY = 3;
const Collision NO_COLLISION = { Collision::EMPTY, Collision::NONE, 0, 0 };


// ------------------------------ GAME ------------------------------
class Game: private GameStateMachine
{
public:
	// ----- TEXTURES -----
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIO,
		SUPERMARIO,
		BLOCK,
		MUSHROOM,
		GOOMBA,
		KOOPA,
		COIN,
		LIFT,
		PORTADA,
		CONTINUAR,
		SALIR,
		NUMBERS,
		VOLVER,
		NOMBREMARIO,
		NIVEL1,
		NIVEL2,
		PIRANHA,
		PLANT,
		GAMEOVER,
		GANADO,
		SHELL,
		STAR,
		FIREMARIO,
		NUM_TEXTURES  // Truco C++: número de texturas definidas
	};

	// Constante globales
	static constexpr uint WIN_WIDTH = TILE_SIDE * WINDOW_WIDTH;  // ancho ventana
	static constexpr uint WIN_HEIGHT = TILE_SIDE * WINDOW_HEIGHT; // alto ventana

	using GameStateMachine::pushState;
	using GameStateMachine::replaceState;

private:
	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	std::array<Texture*, NUM_TEXTURES> textures;

	// ----- SDL -----
	SDL_Window* window = nullptr;	  // puntero a Ventana de la SDL
	SDL_Renderer* renderer = nullptr; // puntero a Renderizador de la SDL (para dibujar)
	SDL_Event event; // evento a pollear

	// maquina de estados
	GameStateMachine* gsMachine;

	bool exit; // salida de juego

	uint32_t startTime, frameTime;	// manejo de tiempo en run


	// puntuacion del jugador
	int points;

	int currentWorld;
	int maxWorlds;

	bool isVictory;
	int marioState;

public:
	// ---- constructora ----
	Game();

	// ---- destructora ----
	~Game();

	// ---- run ----
	// inicializa elementos del juego
	void init();

	// ---- run ----
	// bucle principal del juego
	void run();

	// ---- render ----s
	// renderiza la pantalla
	void render();

	// ---- update ----
	// actualiza el estado de juego
	void update();

	void handleEvents();
	int getCurrentLevel() const { return currentWorld; }
	void setCurrentLevel(int c) { currentWorld = c; }
	int getMaxWorlds() const { return maxWorlds; }

	// ----- GETTERS -----
	uint getWinWidth() const { return WIN_WIDTH; }
	uint getWinHeight() const { return WIN_HEIGHT; }

	Texture* getTexture(TextureName name) const;

	SDL_Renderer* getRenderer() { return renderer; }

	bool GetExit() const { return exit; }

	// maquina de estados
	GameStateMachine* getgsMachine() const { return gsMachine; }

	int getMarioState() const { return marioState; }
	void setMarioState(int s) { marioState = s; }

	// ----- SETTERS -----
	void setExit(bool aux) { exit = aux; }

	void givePoints(int p)
	{
		points += p;
	}

	int getPoints() { return points; }

private:
	// ---- loadTexture ----
	// se cargan las texturas y se guardan en el array
	void loadTextures();

	// ---- playerLives ----
	// muestra en consola las vidas del jugador
	void playerLives();
};

inline Texture*
Game::getTexture(TextureName name) const { return textures[name];}

#endif // GAME_H 
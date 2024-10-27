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
#include "texture.h"
#include "Vector2D.h"
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
					MARIO_SPEED = 1 * TIME_BT_FRAMES;	// velocidad de mario

	// para render de tilemap
	static constexpr int TILE_SIDE = 32;  // constantes estáticas en Game
	static constexpr int WINDOW_WIDTH = 18;
	static constexpr int WINDOW_HEIGHT = 16;



// ------------------------------ GAME ------------------------------
class Game
{
public:
	// ----- TEXTURES -----
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		MARIO,
		NUM_TEXTURES  // Truco C++: número de texturas definidas
	};


private:
	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	std::array<Texture*, NUM_TEXTURES> textures;

	// ----- SDL -----
	SDL_Window* window = nullptr;	  // puntero a Ventana de la SDL
	SDL_Renderer* renderer = nullptr; // puntero a Renderizador de la SDL (para dibujar)

	// Constante globales
	static constexpr uint WIN_WIDTH = TILE_SIDE * WINDOW_WIDTH;  // ancho ventana
	static constexpr uint WIN_HEIGHT = TILE_SIDE * WINDOW_HEIGHT; // alto ventana

	bool exit; // salida de juego

	TileMap* tilemap = nullptr;

	// declaración de los elementos de juego -> con el tipo vector (?)
	Player* player = nullptr;

	// crea semilla
	std::mt19937_64 randomGenerator;
	uint32_t startTime, frameTime;	// manejo de tiempo en run

	int mapOffset = 0; // desplazamiento actual de mapa, llevará la coordenada x del extremo izquierdo de la vista (inicialmente cero)


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

	// ---- render ----
	// renderiza la pantalla
	void render() const;

	// ---- update ----
	// actualiza el estado de juego
	void update();

	// ---- handleEvents ----
	// input del jugador
	void handleEvents();

	// ---- collides ----
	// Los goombas, koopas y mushrooms:
	// - se mueven en una dir fija
	// - caen si dejan de tener un obstaculo a sus pies / desaparecen si caen por un hueco bajo el suelo del mapa
	// - invierten su dirección si encuentran un obstaculo horizontal
	// Estas cosas requieren que los objetos del juego tengan un puntero a Game para llamar a collides
	void collides();

	// ----- GETTERS -----
	uint getWinWidth() { return WIN_HEIGHT; }
	uint getWinHeight() { return WIN_HEIGHT; }
	int getMapOffset() { return mapOffset; }
	Texture* getTexture(TextureName name) const;
	SDL_Renderer* getRenderer() { return renderer; }
	bool GetExit() { return exit; }
	int getRandomRange(int min, int max) { return std::uniform_int_distribution<int>(min, max)(randomGenerator); }

	// ----- SETTERS -----
	void EndGame();
	void setExit(bool aux) { exit = aux; }

private:
	// ---- loadTexture ----
	// se cargan las texturas y se guardan en el array
	void loadTextures();

	// ---- loadMap ----
	void loadObjectMap(std::ifstream& mapa);

	// ---- renderBackground ----
	void renderBackground();

	// ---- playerLives ----
	// muestra en consola las vidas del jugador
	void playerLives();
};

inline Texture*
Game::getTexture(TextureName name) const { return textures[name];}

#endif // GAME_H 
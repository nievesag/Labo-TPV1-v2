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
	// classes
#include "texture.h"
/*#include "Vector2D.h"

// GAME OBJECTS
#include "Player.h"
#include "Block.h"
#include "Goomba.h"
#include "Mushroom.h"
#include "Koopa.h"*/

using uint = unsigned int;

// gestion de frames y framerate 
static constexpr double
					FRAMERATE = 50,						// frames por segundo
					TIME_BT_FRAMES = 1 / FRAMERATE;		// tiempo entre frames

// ------------------------------ GAME ------------------------------
class Game
{
public:
	// ----- TEXTURES -----
	// Identificadores de las texturas
	enum TextureName {
		BACKGROUND,
		DOG,
		HELICOPTER,
		NUM_TEXTURES,  // Truco C++: número de texturas definidas
	};


private:
	// ARRAY DE TEXTURAS -> array estático de tam NUM_TEXTURES de elementos de tipo Texture* 
	std::array<Texture*, NUM_TEXTURES> textures;

	// ----- SDL -----
	SDL_Window* window = nullptr;	  // puntero a Ventana de la SDL
	SDL_Renderer* renderer = nullptr; // puntero a Renderizador de la SDL (para dibujar)

	// Constante globales
	static constexpr uint WIN_WIDTH = 800;  // ancho ventana
	static constexpr uint WIN_HEIGHT = 600; // alto ventana

	bool exit; // salida de juego

	int mapOffset = 0; // desplazamiento actual de mapa

	// declaración de los elementos de juego -> con el tipo vector (?)

	// crea semilla
	std::mt19937_64 randomGenerator;
	uint32_t startTime, frameTime;	// manejo de tiempo en run

public:
	// ---- constructora ----
	Game::Game();

	// ---- destructora ----
	Game::~Game();

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
	int Game::getRandomRange(int min, int max) { return std::uniform_int_distribution<int>(min, max)(randomGenerator); }

	// ----- SETTERS -----
	void EndGame();
	void setExit(bool aux) { exit = aux; }

private:
	// ---- loadTexture ----
	// se cargan las texturas y se guardan en el array
	void loadTextures();

	// ---- loadMap ----
	void loadMap();

	// ---- renderBackground ----
	void renderBackground();

	// ---- playerLives ----
	// muestra en consola las vidas del jugador
	void playerLives();
};

inline Texture*
Game::getTexture(TextureName name) const { return textures[name];}

#endif // GAME_H 
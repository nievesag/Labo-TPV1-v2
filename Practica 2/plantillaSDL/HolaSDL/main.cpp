// MEMORY LEAKS
#include "checkML.h"

// SDL
#include "SDL.h"
#include "SDL_image.h"

// AUX
#include <iostream>
#include <vector>

// GAME
#include "Game.h"

using namespace std;

using uint = unsigned int;

int main(int argc, char* argv[])
{
	Game game;

	game.run();

	return 0;
}
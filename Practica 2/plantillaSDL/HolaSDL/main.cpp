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

// ERRORES
#include "GameError.h"
#include "FileNotFoundError.h"
#include "SDLError.h"
#include "FileFormatError.h" 

int main(int argc, char* argv[])
{
    try {
        // no hace falta borrarlo porque es estatico, se borra solo al salir de ambito (si fuese puntero: delete ay;)
        Game game;
        game.run();
    }

    // GAME ERROR
    catch (GameError& ge) 
    {
        std::cout << ge.what() << std::endl;
    }

    /*
    // ERROR DE SDL
    catch (SDLError& SDLError) {

        std::cout << SDLError.what() << std::endl;
    }

    // ERROR DE ARCHIVO NO ENCONTRADO
    catch (FileNotFoundError& FileNotFoundError) {
        std::cout << FileNotFoundError.what() << std::endl;
    }

    // ERROR DE FORMATO DE ARCHIVO
    catch (FileFormatError& FileFormatError) {
        std::cout << FileFormatError.what() << std::endl;
    }
    */

    // ERROR GENERICO
    catch (...)
    {
        std::cout << "An error occurred, you can't play SuperMario :(" << std::endl;
    }

    return 0;
}
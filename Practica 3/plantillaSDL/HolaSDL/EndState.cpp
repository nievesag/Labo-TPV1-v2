#include "EndState.h"
#include "Game.h"
#include "Button.h"
#include "MainMenuState.h"

EndState::EndState(Game* game, bool victory)
	: GameState(game), victory(victory),
	buttonVolverMenu(new Button(this, game->getTexture(Game::VOLVER), game->getTexture(Game::MUSHROOM), Point2D<double>(125, 100))),
	buttonSalir(new Button(this, game->getTexture(Game::SALIR), game->getTexture(Game::MUSHROOM), Point2D<double>(225, 250)))
{
	// lo mete a la lista de objetos para poder renderizarlos
	addObject(buttonVolverMenu);
	addObject(buttonSalir); 

	// para que los botones puedan reaccionar a eventos
	addEventListener(buttonVolverMenu);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	buttonVolverMenu->connectButton([this]() { volverMenu(); });
	buttonSalir->connectButton([this]() { salir(); });
}

void EndState::render() const
{
	if (victory) game->getTexture(Game::GANADO)->render();
	else game->getTexture(Game::GAMEOVER)->render();

	GameState::render();
}

void EndState::update()
{
	for (auto e : stateList) e->update();
}

void EndState::volverMenu()
{
	// quita los dos estados on TOP, porque siempre seran el propio endgame y el playstate
	game->getgsMachine()->replaceState(new MainMenuState(game));
}

void EndState::salir()
{
	game->setExit(true);
}
#include "PauseState.h"
#include "Button.h"
#include "Game.h"
#include "MainMenuState.h"

PauseState::PauseState(Game* game, PlayState* playState)
	: GameState(game), playState(playState),
	buttonContinuar(new Button(this, game->getTexture(Game::CONTINUAR), game->getTexture(Game::MUSHROOM), Point2D<double>(175, 100))),
	buttonVolverMenu(new Button(this, game->getTexture(Game::VOLVER), game->getTexture(Game::MUSHROOM), Point2D<double>(125, 250))),
	buttonSalir(new Button(this, game->getTexture(Game::SALIR), game->getTexture(Game::MUSHROOM), Point2D<double>(225, 375)))
{
	// lo aniede a la lista de objetos para poder renderizarlo
	addObject(buttonSalir);
	addObject(buttonVolverMenu);
	addObject(buttonContinuar);

	// para que los botones puedan reaccionar a eventos
	addEventListener(buttonContinuar);
	addEventListener(buttonVolverMenu);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	buttonContinuar->connectButton([this]() { continuarPartida(); });
	buttonVolverMenu->connectButton([this]() { volverMenu(); });
	buttonSalir->connectButton([this]() { salir(); });
}

void PauseState::render() const
{
	SDL_SetRenderDrawColor(game->getRenderer(), 0, 0, 0, 255);
	for (auto e : stateList) e->render();
}

void PauseState::update()
{
	for (auto e : stateList) e->update();
}

void PauseState::continuarPartida()
{
	// quita el estado on TOP
	game->getgsMachine()->popState();
}

void PauseState::volverMenu()
{
	// quita los dos estados on TOP, porque siempre seran el propio endgame y el playstate
	game->getgsMachine()->replaceState(new MainMenuState(game));
}

void PauseState::salir()
{
	game->setExit(true);
}
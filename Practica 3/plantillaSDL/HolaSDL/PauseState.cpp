#include "PauseState.h"
#include "Button.h"
#include "Game.h"
#include "MainMenuState.h"

PauseState::PauseState(Game* game, PlayState* playState)
	: GameState(game), playState(playState),
	buttonContinuar(new Button(this, game->getTexture(Game::CONTINUAR), Point2D<double>(0, 0))),
	buttonVolverMenu(new Button(this, game->getTexture(Game::VOLVER), Point2D<double>(0, 100))),
	buttonSalir(new Button(this, game->getTexture(Game::SALIR), Point2D<double>(0, 200)))
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
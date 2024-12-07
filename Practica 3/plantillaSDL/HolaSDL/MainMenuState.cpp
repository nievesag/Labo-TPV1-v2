#include "MainMenuState.h"

#include "Game.h"
#include "PlayState.h"
#include "Button.h"

MainMenuState::MainMenuState(Game* g): GameState(g), 
nivelUno(new Button(this, g->getTexture(Game::NIVEL1), g->getTexture(Game::MUSHROOM), Point2D<double>(200, 275))),
	nivelDos(new Button(this, g->getTexture(Game::NIVEL2), g->getTexture(Game::MUSHROOM), Point2D<double>(200, 325))),
	buttonSalir(new Button(this, g->getTexture(Game::SALIR), g->getTexture(Game::MUSHROOM), Point2D<double>(225, 375)))
{
	// lo mete a la lista de objetos para poder renderizarlos
	addObject(nivelUno);
	addObject(nivelDos);
	addObject(buttonSalir); 

	// para que los botones puedan reaccionar a eventos
	addEventListener(nivelUno);
	addEventListener(nivelDos);
	addEventListener(buttonSalir);

	// uso de la expresion lambda
	nivelUno->connectButton([this]() { loadLevel("1"); });
	nivelDos->connectButton([this]() { loadLevel("2"); });
	buttonSalir->connectButton([this]() { salir(); });
}

void MainMenuState::render() const
{
	// renderiza la imagen de fondo
	game->getTexture(Game::PORTADA)->render();

	for (auto g : stateList) g->render();
}

void MainMenuState::update()
{
	for (auto g : stateList) g->update();
}

void MainMenuState::loadLevel(const std::string& file)
{
	GameState* ps = new PlayState(game, file, "../assets/maps/world");

	// lo pasa al gsMachine que ya luego hace sus cosas
	game->getgsMachine()->pushState(ps);
}

void MainMenuState::salir()
{
	// settea el exit a true (del sdl application)
	game->setExit(true);
}
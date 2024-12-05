#include "MainMenuState.h"

MainMenuState::MainMenuState(Game* game)
	: GameState(game)
{
}

void MainMenuState::render() const
{
	// renderiza la imagen de fondo
	game->getTexture(portada)->render();

	for (auto g : gameList)
	{
		g->render();
	}
}

void MainMenuState::update()
{
	for (auto g : gameList)
	{
		g->update();
	}
}

void MainMenuState::loadLevel()
{
}

void MainMenuState::salir()
{
	// settea el exit a true (del sdl application)
	game->setExit(true);
}
#include "EndState.h"

EndState::EndState(Game* game, bool victory)
	: GameState(game)
{
	// lo aniede a la lista de objetos para poder renderizarlos
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
}

void EndState::update()
{
}

void EndState::volverMenu()
{
}

void EndState::salir()
{
}
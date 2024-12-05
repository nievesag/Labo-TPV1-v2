#pragma once
#include "GameState.h"
class Button;

class EndState : public GameState
{
private:
	// punteros a los botones del GAME OVER MENU
	// botones en este estado: VOLVER AL MENU / SALIR
	Button* buttonVolverMenu;
	Button* buttonSalir;

	// true si se ha ganado la partida -> menu victory
	// false si se ha perdido la partida -> menu game over
	bool victory;

public:
	// constructora
	EndState(Game* game, bool victory);

	// renderizado del estado
	void render() const override;

	void update() override;

private:
	// funciones de los botones
	void volverMenu();
	void salir();
};
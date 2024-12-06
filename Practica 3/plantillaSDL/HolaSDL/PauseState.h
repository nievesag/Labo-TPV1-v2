#ifndef PAUSESTATE_H
#define PAUSESTATE_H

#include "GameState.h"
#include "PlayState.h"

class Button;

class PauseState : public GameState
{
private:
	PlayState* playState;

	// punteros a los botones del PAUSE MENU
	Button* buttonContinuar;
	Button* buttonVolverMenu;
	Button* buttonSalir;

public:
	PauseState(Game* game, PlayState* playState);

	// renderizado del estado
	void render() const override;

	void update() override;

private:
	// funciones de los botones
	void continuarPartida();
	void volverMenu();
	void salir();
};

#endif

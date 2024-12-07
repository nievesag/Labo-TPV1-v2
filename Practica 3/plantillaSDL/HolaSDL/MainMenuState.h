#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"

class Button;

class MainMenuState : public GameState
{
private:
	// punteros a los botones del MAIN MENU
	// botones en este estado: NIVEL 1 / NIVEL 2 / SALIR
	Button* nivelUno;
	Button* nivelDos;
	Button* buttonSalir;

public:
	// constructora
	MainMenuState(Game* g);

	// renderizado del estado
	void render() const override;

	void update() override;


private:
	// funciones de los botones
	void loadLevel(const std::string& file);
	void salir();
};

#endif
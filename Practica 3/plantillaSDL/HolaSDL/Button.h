#ifndef BUTTON_H
#define BUTTON_H
#include <functional>

#include "EventHandler.h"
#include "GameObject.h"
#include "GameState.h"

// utiliza callbacks funcionales de tipo <void(void)>
using SDLEventCallback = std::function<void(void)>;

class Button: public GameObject, EventHandler
{
	// boton en pantalla
	Texture* buttonTexture;	// textura del boton
	Point2D<double> buttonPos;	// posicion del boton en pantalla

	// estados del boton para render y animacion
	int currentFrame;
	enum buttonState {
		MOUSEOUT = 0,
		MOUSEOVER = 1,
		CLICKED = 2
	};

	// lista de funciones a ejecutar en caso de ser pulsado
	std::list<SDLEventCallback> callbacks;

	// cursor
	SDL_Point point;	// guarda posicion del cursor en click
	SDL_Rect destRect;	// rectangulo del render

	// METODOS PRIVADOS
	void emit() const;

public:
	Button(GameState* gameState, Texture* texture, Point2D<double> pos);

	// METODOS PUBLICOS
	// ---- render ----
	void render() const override;

	// ---- update ----
	void update() override;

	// ---- update ----
	void handleEvent(const SDL_Event& event) override;

	// ---- update ----
	void connectButton(const SDLEventCallback& buttonCallback);
};

#endif
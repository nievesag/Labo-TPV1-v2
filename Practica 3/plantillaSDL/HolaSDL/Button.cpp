#include "checkML.h"
#include "Button.h"

Button::Button(GameState* gameState, Texture* texture, Point2D<double> pos)
	: GameObject(gameState), buttonTexture(texture), buttonPos(pos)
{
	// para animacion
	currentFrame = MOUSEOUT; // frame inicial a 0

	point.x = 0;
	point.y = 0;

	// setea posiciones y dimensiones en el destRect
	destRect = SDL_Rect{ (int)pos.getX(), (int)pos.getY(), texture->getFrameWidth(), texture->getFrameHeight() };
}

void Button::emit() const
{
	// llama a todas las funciones registradas
	for (SDLEventCallback buttonCallback : callbacks)
		buttonCallback();
}

void Button::render() const
{
	if (currentFrame == MOUSEOVER) 
	{
		buttonTexture->render(destRect, SDL_Color{ 0,255,0,255 }); // cambia color
		// falta lo del icono del champi
	}
	else buttonTexture->render(destRect);
}

void Button::update()
{
	SDL_GetMouseState(&point.x, &point.y);

	// comprueba si el cursor esta sobre el rectangulo
	if (SDL_PointInRect(&point, &destRect)) currentFrame = MOUSEOVER;
	else currentFrame = MOUSEOUT;
}

void Button::handleEvent(const SDL_Event& event)
{
	// si se pulsa el boton izq del raton
	if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) 
	{
		// guarda pos del cursor al pulsar
		//SDL_Point point{ event.button.x, event.button.y };

		point.x = event.button.x;
		point.y = event.button.y;

		// comprueba si el punto esta en el rect del boton
		if (SDL_PointInRect(&point, &destRect)) 
		{
			currentFrame = CLICKED;

			// se invocan los metodos
			emit();
		}
	}
}

void Button::connectButton(const SDLEventCallback& buttonCallback)
{
	callbacks.push_back(buttonCallback);
}
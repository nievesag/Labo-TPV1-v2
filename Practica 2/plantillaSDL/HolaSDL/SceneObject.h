#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "gameList.h"
#include "Vector2D.h"
#include "texture.h"
#include <list>

class SceneObject : public GameObject
{
	// atributos protegidos
protected:
	Point2D<double> position; // Posicion del objeto
	int width, height;		  // Dimension del objeto
	double speed;			  // Velocidad del objeto

	Texture* texture;

	// rectangulo del render
	SDL_Rect destRect;

	// iterador de la lista
	GameList<SceneObject*>::anchor anchor; // no se si hacer que sea una lista de punteros o no

	// metodos publicos
public:

	// ---- hit ----
	// colisiones
	virtual bool hit(const SDL_Rect& rect, bool fromPlayer);

	void setListAnchor(GameList<SceneObject>::anchor&& anchor)
	{
		// se esta moviendo el argumento al atributo anchor de sceneobject
		anchor = std::move(anchor);
	}
};

#endif
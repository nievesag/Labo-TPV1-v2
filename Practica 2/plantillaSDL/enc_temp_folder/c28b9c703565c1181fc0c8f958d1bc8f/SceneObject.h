#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "GameObject.h"
#include "gameList.h"
#include "Vector2D.h"
#include "texture.h"
#include <list>

#include "Collision.h"

class SceneObject : public GameObject
{
	// atributos protegidos
protected:
	Point2D<int> position; // Posicion del objeto
	int width, height;		  // Dimension del objeto
	Vector2D<double> speed;	  // Velocidad del objeto
	//double speed;			  

	Texture* texture = nullptr;
	Game* game = nullptr;

	// rectangulo del render
	SDL_Rect destRect;

	// iterador de la lista
	GameList<SceneObject*>::anchor anchor; // no se si hacer que sea una lista de punteros o no

	virtual Collision tryToMove(Vector2D<double> v, Collision::Target target);

	// metodos publicos
public:
	SceneObject(Game* g, std::istream& in);

	SceneObject(Game* g, Vector2D<int> p);

	// ---- hit ----
	// colisiones
	virtual Collision hit(const SDL_Rect& rect, Collision::Target t) = 0;
	virtual void render() const override = 0;

	void setListAnchor(GameList<SceneObject>::anchor&& anchor)
	{
		// se esta moviendo el argumento al atributo anchor de sceneobject
		anchor = std::move(anchor);
	}

	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;
};

#endif
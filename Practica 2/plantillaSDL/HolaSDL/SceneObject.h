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
	Point2D<double> position; // Posicion del objeto
	int width, height;		  // Dimension del objeto
	Vector2D<double> speed;	  // Velocidad del objeto
	Vector2D<int> direction;
	//double speed;	

	Texture* texture = nullptr;
	Game* game = nullptr;

	// rectangulo del render
	SDL_Rect destRect;

	// iterador de la lista
	GameList<SceneObject>::anchor _anchor;

	virtual Collision tryToMove(Vector2D<double> v, Collision::Target target);


	// metodos publicos
public:
	SceneObject(Game* g,Point2D<double> pos, Texture* t);

	// ---- hit ----
	// colisiones
	virtual Collision hit(const SDL_Rect& rect, Collision::Target t) = 0;
	virtual void manageCollisions(Collision collision) = 0;
	virtual void render() const override = 0;

	void setListAnchor(GameList<SceneObject>::anchor&& anchor)
	{
		// se esta moviendo el argumento al atributo anchor de sceneobject
		_anchor = std::move(anchor);
	}

	SDL_Rect getCollisionRect() const;
	SDL_Rect getRenderRect() const;

	// Para gestion de cola de objetos ->
	//	Se usa para poder clonar los objetos polimorficamente e insertar copias en la lista de objetos del juego
	//	Para evitar tener que recargar el mapa desde el archivo al reiniciar el nivel (muere mario)
	//	Hay que tener en cuenta que cuando se reinicia el nivel todos los objetos del juego (salvo el jugador y
	//	el tilemap) han de ser destruidos y reemplazados por objetos nuevos
	//	Lo mismo ha de ocurrir si el reinicio se produce en un punto de control y no al principio del mapa
	virtual SceneObject* clone() const = 0;
};

#endif
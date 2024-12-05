#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include "GameState.h"

class PlayState : public GameState 
{
	// desplazamiento actual de mapa, llevará la coordenada x del extremo izquierdo de la vista 
	// (inicialmente cero)
	int mapOffset;

	// declaración de los elementos de juego
	SceneObject* player;
	SceneObject* tilemap;

	GameList<SceneObject> gameList;

	// --- mecanismo para insertar los objetos del juego solo cuando se vuelven visibles en el mapa ---
	// (en el caso de los objetos animados, esto es imprescindible para que aparezcan en la posicion esperada)

	// vector sobre el que leer los objetos al cargar el mapa
	// utilizando un contador se podran extraer los objetos de esa cola conforme vayan haciendose visibles y
	// para evitar tener que recargar el mapa desde el archivo al reiniciar el nivel
	// (porque Mario haya sido herido) se recomienda utilizar un metodo virtual puro
	std::vector<SceneObject*> objectQueue;

	// indice de la secuencia, siguiente objeto a ser metido si esta dentro de la vista
	// (siempre se añaden en orden porque la lista esta ordenada por abscisas)
	int nextObject;


public:
	// constructora
	PlayState(Game* game, const std::string& file, const std::string& root);

	int getMapOffset() { return mapOffset; } // no se si esto deberia guardarlo el playstate o el game


	void playerLives();

	void loadObjectMap(std::ifstream& mapa);

	void update();

	void deleteEntities();

	void createSeta(Point2D<int> p);

	void render();

	void addVisibleEntities();

	void reloadWorld(const std::string& file, const std::string& root);

	void addObject(SceneObject* o);

	Collision checkCollisions(const SDL_Rect& rect, Collision::Target target);
};

#endif
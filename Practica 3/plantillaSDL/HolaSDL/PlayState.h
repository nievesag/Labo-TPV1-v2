#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include <vector>
#include "GameState.h"
#include "Player.h"
#include "Infobar.h"

class PlayState : public GameState 
{
private:
	// desplazamiento actual de mapa, llevar� la coordenada x del extremo izquierdo de la vista 
	// (inicialmente cero)
	int mapOffset;

	// declaraci�n de los elementos de juego
	Player* player = nullptr;
	SceneObject* tilemap;
	InfoBar* infobar;

	GameList<SceneObject> gameList;

	bool falled = false;

	// --- mecanismo para insertar los objetos del juego solo cuando se vuelven visibles en el mapa ---
	// (en el caso de los objetos animados, esto es imprescindible para que aparezcan en la posicion esperada)

	// vector sobre el que leer los objetos al cargar el mapa
	// utilizando un contador se podran extraer los objetos de esa cola conforme vayan haciendose visibles y
	// para evitar tener que recargar el mapa desde el archivo al reiniciar el nivel
	// (porque Mario haya sido herido) se recomienda utilizar un metodo virtual puro
	std::vector<SceneObject*> objectQueue;

	// indice de la secuencia, siguiente objeto a ser metido si esta dentro de la vista
	// (siempre se a�aden en orden porque la lista esta ordenada por abscisas)
	int nextObject;
	// color de fondo
	int r, g, b;

	bool isVictory;
	bool endVictory;

public:
	// constructora
	PlayState(Game* g, const std::string& file, const std::string& root);

	void addMapOffset(int newOffset) { mapOffset += newOffset; }
	void setMapOffset(int newOffset) { mapOffset = newOffset; }
	int getMapOffset() const { return mapOffset; } // no se si esto deberia guardarlo el playstate o el game
	void setVictory(bool v) { isVictory = v; }
	void setFalled(bool f) { falled = f; }
	bool getHasFalled() const { return falled; }
	void setEndVictory(bool v) { endVictory = v; }

	Player* getPlayer() { return player; }

	void playerLives();

	void loadObjectMap(std::ifstream& mapa);

	void update();

	void deleteEntities();

	void createSeta(Point2D<int> p);

	void render() const override;

	void addVisibleEntities();

	void reloadWorld(const std::string& file, const std::string& root);

	void loadLevel(const std::string& file, const std::string& root);

	void addObject(SceneObject* o);

	Collision checkCollisions(const SDL_Rect& rect, Collision::Target target);

	// ---- handleEvents ----
	// input del jugador
	void handleEvent(const SDL_Event& event) override;
};

#endif
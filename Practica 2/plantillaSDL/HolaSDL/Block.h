#ifndef BLOCK_H
#define BLOCK_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "Texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

#include "Collision.h"
#include "SceneObject.h"

class Game;

using uint = unsigned int;
using namespace std;

class Block : public SceneObject
{
	// atributos privados
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	Point2D<double> position;	// posicion actual en Point2D

	char tipoL;
	int tipo;
	enum Tipo // tipo de bloque
	{
		LADRILLO, SORPRESA, OCULTO, VACIO
	};

	char accionL;
	int accion;
	enum Accion // accion
	{
		POTENCIADOR, MONEDA
	};

	// Guia de bloques txt
	// TIPO
	// ? -> sorpresa
	// B -> ladrillo
	// H -> oculto
	// ACCION
	// P -> potenciador
	// C -> moneda

	bool alive;

	int blockFrame;
	int animationFrame = 0;   // Contador para el ciclo de caminar
	int frameTimer = 0;

	SDL_Rect destRect;

public:
	Block(Game* g, std::istream& in);

	// -- render --
	void render(SDL_Rect destRect) const override;

	// -- update --
	void update();

	void updateRect();

	// -- hit --
	// controla las colisiones
	// Los bloques son obstaculos para todos los personajes cuando lo golpeen desde arriba o desde un lateral
	// Si Mario lo golpa desde abajo:
	//	-> si el bloque es de ladrillo y el player es SuperMario: bloque se rompe
	//	-> si el bloque es sorpresa/oculto y accion es potenciador: saca mushroom sobre el bloque y lo hace vacio
	//	-> nada en el resto de casos
	Collision hit(const SDL_Rect& rect, bool fromPlayer) override;

	bool getAlive() {
		return alive;
	}

	int getTipo() {
		return tipo;
	}

	void setTipo(int t)
	{
		tipo = t;
	}

	void manageSorpresa();

	void killBlock() { alive = false; }

	Point2D<double> getPos() const { return position; }
};

#endif
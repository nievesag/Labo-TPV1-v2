#ifndef BLOCK_H
#define BLOCK_H

#include "checkML.h"
#include <SDL.h>
#include "Vector2D.h"
#include "texture.h"
#include <istream>
#include <iostream>
#include <fstream>
#include <string>

class Game;

using uint = unsigned int;
using namespace std;

class Block
{
	// atributos privados
private:
	Texture* texture = nullptr;	// puntero a su textura
	Game* game = nullptr;		// puntero al juego

	Point2D<double> position;	// posicion actual en Point2D

	enum Tipo // tipo de bloque
	{
		LADRILLO, SORPRESA, VACIO, OCULTO
	};

	enum Accion // accion
	{
		POTENCIADOR, MONEDA
	};

public:
	Block();

	// -- render --
	void render() const;

	// -- update --
	void update();

	// -- hit --
	// controla las colisiones
	// Los bloques son obstaculos para todos los personajes cuando lo golpeen desde arriba o desde un lateral
	// Si Mario lo golpa desde abajo:
	//	-> si el bloque es de ladrillo y el player es SuperMario: bloque se rompe
	//	-> si el bloque es sorpresa/oculto y accion es potenciador: saca mushroom sobre el bloque y lo hace vacio
	//	-> nada en el resto de casos
	void hit(SDL_Rect* rect);
};

#endif
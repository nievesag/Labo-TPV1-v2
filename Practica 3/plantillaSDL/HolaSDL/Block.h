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
	int tipo;
	enum Tipo // tipo de bloque
	{
		LADRILLO, SORPRESA, OCULTO, VACIO
	};

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

	//SDL_Rect destRect;

public:
	Block(Game* g, Point2D<int> p, Texture* t, char tipoL, char accionL);

	// -- render --
	void render() override;

	// -- update --
	void update() override;

	// -- hit --
	Collision hit(const SDL_Rect& rect, Collision::Target t) override;

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

	Point2D<int> getPos() const { return position; }

	virtual void manageCollisions(Collision col) override;

	SceneObject* clone() const override;

	void updateAnim() override;

	//void updateRect() override;
};

#endif
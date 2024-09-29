#pragma once

#include "Ejemplar.h"

class Catalogo
{
	// atributos privados
private:
	// array dinamico ArrayCatalogo de punteros a estructuras de tipo Ejemplar
	Ejemplar* ArrayCatalogo;
	Ejemplar* ejemplar;
	int tamArrayCatalogo;

	// metodos publicos
public:
	// constructora
	Catalogo() : ArrayCatalogo(nullptr), tamArrayCatalogo(0) {};

	bool leerCatalogo();
	Ejemplar* buscarEjemplar(int cod, int ini, int fin);

	~Catalogo();

	// setter
	int setTam(int tam)
	{
		tamArrayCatalogo = tam;
	}

	// Getter
	int getTam()
	{
		return tamArrayCatalogo;
	}

	void setEjemplar(Ejemplar* e)
	{
		ejemplar = e;
	}

	Ejemplar* getEjemplar(int pos)
	{
		return &ArrayCatalogo[pos];
	}
};
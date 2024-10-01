#pragma once

#include "Ejemplar.h"
#include "checkML.h"

class Catalogo
{
	// atributos privados
private:
	// array dinamico ArrayCatalogo de punteros a estructuras de tipo Ejemplar
	Ejemplar* ArrayCatalogo;
	int tamArrayCatalogo;
	int maxArrayCatalogo;

	// metodos publicos
public:
	// constructora
	Catalogo();
	Catalogo(std::istream&);

	// destructora
	~Catalogo();

	// lectura
	bool leerCatalogo();

	// Getters
	int getTam() { return tamArrayCatalogo; }
	Ejemplar* getEjemplar(int pos) const { return &ArrayCatalogo[pos]; }

	// metodos
	Ejemplar* buscarEjemplar(int cod, int ini, int fin) const;
	void insertaEjemplar(char tipo, std::string nombre);

	// render
	void mostrarCatalogo();
};
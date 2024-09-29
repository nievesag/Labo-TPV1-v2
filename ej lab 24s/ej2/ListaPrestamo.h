#pragma once

#include "Prestamo.h"
#include "Catalogo.h"

class ListaPrestamo
{
	// atributos privados
private:
	// array dinamico ArrayPrestamo de punteros a estructuras de tipo Prestamo
	Prestamo* ArrayPrestamo;
	Prestamo* prestamo;
	int tamArrayPrestamo;

	// metodos publicos
public:
	// constructora
	ListaPrestamo() : ArrayPrestamo(nullptr), tamArrayPrestamo(0) {};

	bool leerPrestamos(Catalogo& catalogo);
	void OrdenarPrestamos();
};
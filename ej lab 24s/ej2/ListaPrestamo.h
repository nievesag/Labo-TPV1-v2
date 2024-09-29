#pragma once

#include "Prestamo.h"
#include "Catalogo.h"

class ListaPrestamo
{
	// atributos privados
private:
	// array dinamico ArrayPrestamo de punteros a estructuras de tipo Prestamo
	Prestamo* ArrayPrestamo;
	int tamArrayPrestamo;

	// metodos publicos
public:
	// constructora
	ListaPrestamo() : ArrayPrestamo(nullptr), tamArrayPrestamo(0) {};

	bool leerPrestamos(Catalogo& catalogo);
	void ordenarPrestamos();
	void mostrarPrestamos();

	friend std::ostream& operator<<(std::ostream& out, const ListaPrestamo&);
};
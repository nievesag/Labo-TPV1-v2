#pragma once

#include "Prestamo.h"
#include "Catalogo.h"
#include "checkML.h"

class ListaPrestamo
{
	// atributos privados
private:
	// array dinamico ArrayPrestamo de punteros a estructuras de tipo Prestamo
	Prestamo* ArrayPrestamo;
	int tamArrayPrestamo;
	int maxArrayPrestamo;

	// metodos publicos
public:
	// constructora
	ListaPrestamo(std::istream& const e, const Catalogo& c);

	// destructora
	~ListaPrestamo();

	// operador salida
	friend std::ostream& operator<<(std::ostream& out, const ListaPrestamo&);

	// lectura
	bool leerPrestamos(Catalogo& catalogo); // esto ya no se lee aqui

	// metodos
	void ordenarPrestamos();
	void insertaPrestamo(const Prestamo&);

	// render
	void mostrarPrestamos();
};
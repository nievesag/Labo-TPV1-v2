#pragma once

#include "Date.h"
#include "Ejemplar.h"

class Prestamo
{
    // atributos privados
private:
    Ejemplar* ejemplar;
	Date* fecha;
	Date* fechaDevolucion;
    int user;

    // metodos publicos
public:
    // constructoras
    Prestamo() : fecha(), user(0) {};
    Prestamo(Date* date, int user);
    Prestamo(const Prestamo& alquiler);


	// declaracion de operadores
	// lee
	friend std::istream& operator>>(std::istream& in, Prestamo& p);
	// escribe
	friend std::ostream& operator<<(std::ostream& in, const Prestamo& p);

	// para acceso externo a variables privadas

	// Setter
	void setUser(int u)
	{
		user = u;
	}

	// Getter
	char getUser()
	{
		return user;
	}

	// Setter
	void setDate(int day, int month, int year)
	{
		fecha = new Date(day, month, year);
	}

	Date* getDate()
	{
		return fecha;
	}

	Date* getDateDevol(Prestamo* prestamo)
	{
		return fecha + duracionPrestamo((*prestamo->ejemplar).getTipo());
	}

	int duracionPrestamo(int tipo)
	{
		// libros
		if(tipo == 0)
		{
			return 30;
		}

		// audiovisual
		if(tipo == 1)
		{
			return 7;
		}

		// juegos
		if(tipo == 2)
		{
			return 14;
		}
	}

	void setEjemplar(Ejemplar* e)
	{
		ejemplar = e;
	}

	Ejemplar* getEjemplar()
	{
		return ejemplar;
	}
};
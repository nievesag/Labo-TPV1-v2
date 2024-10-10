#pragma once

#include "Date.h"
#include "Ejemplar.h"
#include "checkML.h"
#include "Catalogo.h"

class Prestamo
{
    // atributos privados
private:
    Ejemplar* ejemplar;

	Date fecha;
	Date fechaDevolucion;

    int user;

    // metodos publicos
public:
    // constructoras
	Prestamo();
    Prestamo(Ejemplar* e, Date f, int u);

	// ----- declaracion de operadores
	// lee
	friend std::istream& operator>>(std::istream& in, Prestamo& p);
	// escribe
	friend std::ostream& operator<<(std::ostream& out, const Prestamo& p);
	// comparación
	bool operator<(const Prestamo& prestamo) const;

	// ----- para acceso externo a variables privadas
	// --- usuario
	// Setter
	void setUser(int u) { user = u; }
	// Getter
	char getUser() const { return user; }

	// --- fecha
	// Setter
	void setDate(Date f) { fecha = f; }
	void setDateDevol(Date f) { fechaDevolucion = f; }
	// Getters
	Date getDate() const { return fecha; }
	Date getDateDevol() const { return fecha + duracionPrestamo((*this->ejemplar).getTipo()); }

	// --- ejemplar
	// Setter
	void setEjemplar(Ejemplar* e) { ejemplar = e; } ;
	// Getter
	Ejemplar* getEjemplar() const { return ejemplar; }

	// ----- metodos
	// calcula duracion de prestamo
	int duracionPrestamo(int tipo) const
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

	const int quedanDias()
	{
		Date* hoy = new Date();
		Date devol = getDateDevol();
		int quedan = (devol.diff(*hoy));
		delete hoy;
		return quedan;
	}

	const int penal()
	{
		Date* hoy = new Date();
		Date devol = getDateDevol();
		int quedan = (devol.diff(*hoy));
		delete hoy;

		int const pen = abs(quedan) * 2;
		return pen;
	}

	void leePrestamo(const Catalogo&);
};
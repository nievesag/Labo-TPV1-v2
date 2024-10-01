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
	char getUser() { return user; }

	// --- fecha
	// Setter
	void setDate(Date f) { fecha = f; }
	void setDateDevol(Date f) { fechaDevolucion = f; }
	// Getters
	Date getDate() { return fecha; }
	Date getDateDevol() const { return fecha + duracionPrestamo((*this->ejemplar).getTipo()); }

	// --- ejemplar
	// Setter
	void setEjemplar(Ejemplar* e) { ejemplar = e; }
	// Getter
	Ejemplar* getEjemplar() { return ejemplar; }

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

	void leePrestamo(const Catalogo&);
};
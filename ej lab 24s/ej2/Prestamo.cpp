#include "Prestamo.h"

Prestamo::Prestamo()
{

}

Prestamo::Prestamo(Ejemplar* e, Date f, int u) : ejemplar(e), fecha(f), user(u)
{
	
}

bool Prestamo::operator<(const Prestamo& prestamo) const
{
	return false;
}

void Prestamo::leePrestamo(const Catalogo&)
{

}
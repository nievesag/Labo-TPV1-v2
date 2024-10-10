#include "Prestamo.h"
#include <format>

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

std::ostream& operator<<(std::ostream& out, const Prestamo& p)
{
	//Date* hoy = new Date();
	//Date devol = p.getDateDevol();
	//int quedan = (devol.diff(*hoy));
	//int pen = abs(quedan) * 2;
	//delete hoy;

	//out << std::format("{} (en {} dias) {} ({} dias de penalizacion)", p.getDate(), quedan, p.getEjemplar()->getNombre(), pen);
	return out;
}
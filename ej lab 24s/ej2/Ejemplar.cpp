#include "Ejemplar.h"

Ejemplar::Ejemplar()
{

}

Ejemplar::Ejemplar(int c, char t, std::string n)
{

}

void Ejemplar::presta()
{
	this->disponible = false;
}

void Ejemplar::devuelve()
{
	this->disponible = true;
}
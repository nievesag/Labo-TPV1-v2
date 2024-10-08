#include "Ejemplar.h"

Ejemplar::Ejemplar()
{

}

Ejemplar::Ejemplar(int c, char t, std::string n) : codigo(c), t(t), nombre(n)
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
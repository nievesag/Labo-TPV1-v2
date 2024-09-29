#pragma once

#include <string>

class Ejemplar
{
	// atributos privados
private:
	int codigo;
	
	enum Tipo
	{
		LIBRO, AUDIOVISUAL, JUEGO
	};

	int t;

	std::string nombre;

	// metodos publicos
public:
	// constructoras
	Ejemplar() : codigo(0), t(0), nombre("") {};
	Ejemplar(int c, char t, std::string n);
	Ejemplar(const Ejemplar& coche);

	// declaracion de operadores
	// lee
	friend std::istream& operator>>(std::istream& in, Ejemplar& e);
	// escribe
	friend std::ostream& operator<<(std::ostream& in, const Ejemplar& e);

	// para acceso externo a variables privadas
	// Setter
	void setCodigo(int c)
	{
		codigo = c;
	}

	// Getter
	int getCodigo()
	{
		return codigo;
	}

	// Setter
	void setTipo(int tipo)
	{
		t = Tipo(tipo);
	}

	// Getter
	int getTipo()
	{
		return Tipo(t);
	}

	// Setter
	void setNombre(std::string n)
	{
		nombre = n;
	}

	// Getter
	std::string getNombre()
	{
		return nombre;
	}
};
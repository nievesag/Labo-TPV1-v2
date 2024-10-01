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

	bool disponible;

	// metodos publicos
public:
	// constructoras
	Ejemplar();
	Ejemplar(int c, char t, std::string n);

	// ----- declaracion de operadores
	// lee
	friend std::istream& operator>>(std::istream& in, Ejemplar& e);
	// escribe
	friend std::ostream& operator<<(std::ostream& out, const Ejemplar& e);

	// ----- acceso externo a variables privadas
	// --- codigo
	// Setter
	void setCodigo(int c) { codigo = c; }
	// Getter
	int getCodigo() { return codigo; }

	// --- tipo
	// Setter
	void setTipo(int tipo) { t = Tipo(tipo); }
	// Getter
	int getTipo() { return Tipo(t); }

	// --- nombre
	// Setter
	void setNombre(std::string n) { nombre = n; }
	// Getter
	std::string getNombre() const { return nombre; }

	// ----- metodos
	void presta();
	void devuelve();
};
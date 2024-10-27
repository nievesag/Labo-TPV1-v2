#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <ostream>

// !!! por las plantillas usar definiciones de funciones en el h ->
// el codigo depende del argumento que le pases (codigo no cerrado)

template <typename T>
class Vector2D
{
	// variables privadas
private:
	T x, y;

	// metodos publicos
public:
	// ---- CONSTRUCTORAS ----
	Vector2D(T x, T y)
		: x(x), y(y) {}

	// ---- SETTERS Y GETTERS ----
	// ---- getters ----
	T getX() { return x; }
	T getY() { return y; }
	// ---- setters ----
	void setX(T newX) { x = newX; }
	void setY(T newY) { y = newY; }

	// ---- OPERADORES ----
	// operador +
	Vector2D operator+(const Vector2D& v) const
	{
		Vector2D suma;

		suma.x = x + v.x;
		suma.y = y + v.y;

		return suma;
	}

	// operador -
	Vector2D operator-(const Vector2D& v) const
	{
		Vector2D resta;

		resta.x = x - v.x;
		resta.y = y - v.y;

		return resta;
	}

	// operador producto escalar *
	Vector2D operator*(double d) const
	{
		Vector2D escalar;

		escalar.x = x * d;
		escalar.y = y * d;

		return escalar;
	}

	// operador producto vector-escalar *
	T operator*(const Vector2D& d) const
	{
		return d.x * x + d.y * y;
	}

	// operador salida consola <<
	friend std::ostream& operator<<(std::ostream& os, const Vector2D& v)
	{
		os << "(" << v.x << "," << v.y << ")";
		return os;
	}

	// operador entrada consola >>
	friend std::istream& operator>>(std::istream& is, Vector2D& v)
	{
		is >> v.x >> v.y;
		return is;
	}
};

// establecer alias Point2D
// igualar T a int o double??
template <class T> using Point2D = Vector2D<T>;

#endif
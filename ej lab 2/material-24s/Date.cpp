//
// Implementación de la clase Date
//

#include <format>
#include <chrono>

#include "Date.h"

#include <fstream>

using namespace std;

Date::Date() {
	using namespace std::chrono;

	// Obtiene la fecha actual con la biblioteca chrono de C++20
	year_month_day ymd(floor<std::chrono::days>(time_point(system_clock::now())));

	// Obtiene cada campo
	day = static_cast<unsigned>(ymd.day());
	month = static_cast<unsigned>(ymd.month());
	year = static_cast<int>(ymd.year()) - 2000;
}

Date::Date(int d, int m, int y)
 : day(d), month(m), year(y) {
	if (!correctDate())
		throw "Invalid date"s;
}

Date::Date(const Date& date)
 : day(date.day), month(date.month), year(date.year) { }

void Date::operator++() {
	day++;

	// Pasa de mes
	if (day > daysInMonth(month, year)){
		day = 1;
		month++;
		// Pasa de año
		if (month > 12){
			month = 1;
			year++;
		}
	}
}

void Date::operator+=(int n) {
	// Esta implementación no es eficiente, pues suma días
	// y comprueba el paso de meses y años de uno en uno

	for (int i = 0; i < n; i++)
		operator++();
}

bool Date::operator<(const Date& date) const {
	// Orden lexicográfico
	return (year < date.year ||
	       (year == date.year && (month < date.month ||
	                             (month == date.month && day < date.day))));
}


int Date::diff(const Date& date) const {
	return calculateValue() - date.calculateValue();
}

// Métodos privados

int Date::calculateValue() const{
	// Días desde el año 2000
	int v = 365 * (year - 1) + ((year - 1) / 4 + 1 - (year - 1) / 100 + (year - 1) / 400);

	// Suma los días de los meses anteriores
	for (int m = month - 1; m > 0; m--)
		v += daysInMonth(m, year);

	return v + day;
}

int Date::daysInMonth(int month, int year) {
	int numDays = 0;

	switch (month) {
		case 4: case 6: case 9: case 11:
			numDays = 30;
			break;
		case 2:
			numDays = leapYear(year) ? 29 : 28;
			break;
		default:
			numDays = 31;
	}

	return numDays;
}

bool Date::leapYear(int year) {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

bool Date::correctDate() const {
	return year >= 0
	       && month >= 1 && month <= 12
	       && day >= 1 && day <= daysInMonth(month, year);
}

istream& operator>>(istream& in, Date& d){
	char c;
	return (in >> d.day >> c >> d.month >> c >> d.year);
}

ostream& operator<<(ostream& out, const Date& d){
	out << format("{:0>2}/{:0>2}/{:0>2}", d.day, d.month, d.year);
	return out;
}

#include "ListaPrestamo.h"
#include <fstream>

bool ListaPrestamo::leerPrestamos(Catalogo& catalogo)
{
    // abre el archivo coches.txt
    std::fstream prestamoRead("prestamos.txt");

    int c; // codigo del ejemplar
    int u; // usuario del prestamo

    // fecha del prestamo
    int day;
    int month;
    int year;
    char barra;

    // saca el tamaño de la lista de coches
    prestamoRead >> tamArrayPrestamo;

    // crea el array dinamico
    ArrayPrestamo = new Prestamo[tamArrayPrestamo];

    // bucle para leer los datos
    for (int i = 0; i < tamArrayPrestamo; i++)
    {
        prestamoRead >> c; // lee el codigo
        ArrayPrestamo[i].setEjemplar(catalogo.buscarEjemplar(c)); // lo mete

        // lee la fecha
    	barra = ' ';
        day = 0;
        month = 0;
        year = 0;

        prestamoRead >> day;
        prestamoRead >> barra;
        prestamoRead >> month;
        prestamoRead >> barra;
        prestamoRead >> year;

        ArrayPrestamo[i].setDate(day, month, year); // lo mete

        prestamoRead >> u; // lee el user
        ArrayPrestamo[i].setUser(u); // lo mete 
    }

    return prestamoRead.is_open(); // true -> archivo prestamos abierto / false -> error  
}

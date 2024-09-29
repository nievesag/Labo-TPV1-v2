// ej2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <array>
#include <fstream>

#include "Date.h"
#include "Catalogo.h"
#include "ListaPrestamo.h"

int main()
{
    Catalogo catalogo;
    ListaPrestamo listaPrestamo;

    catalogo.leerCatalogo();
    listaPrestamo.leerPrestamos(catalogo);

    listaPrestamo.ordenarPrestamos();

    listaPrestamo.mostrarPrestamos();

    catalogo.~Catalogo();
    listaPrestamo.~ListaPrestamo();
}
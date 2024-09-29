// Nieves Alonso Gilsanz

#include "Catalogo.h"
#include "ListaPrestamo.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Catalogo catalogo;
    ListaPrestamo listaPrestamo;

    catalogo.leerCatalogo();
    listaPrestamo.leerPrestamos(catalogo);

    listaPrestamo.ordenarPrestamos();

    listaPrestamo.mostrarPrestamos();

    return 0;
}
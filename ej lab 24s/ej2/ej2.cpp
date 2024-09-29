// Nieves Alonso Gilsanz

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

    return 0;
}
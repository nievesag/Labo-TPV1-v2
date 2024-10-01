// Nieves Alonso Gilsanz

#include "Catalogo.h"
#include "ListaPrestamo.h"
#include <windows.h>

int main()
{
    SetConsoleOutputCP(CP_UTF8);

    Catalogo catalogo;
    ListaPrestamo listaPrestamo;

    // carga catalogo y lista prestamos
    catalogo.leerCatalogo();
    listaPrestamo.leerPrestamos(catalogo);

    // ordena prestamos
    listaPrestamo.ordenarPrestamos();

    // mostrar un menú con opciones para:
    //  - mostrar el catálogo
    //  - mostrar los préstamos
    //  - añadir un nuevo ejemplar (*)
    //  - prestar un ejemplar (*)
    //  - devolver un ejemplar (*)
    //  - salir

    // (*) Al añadir un ejemplar o préstamo la lista correspondiente debe quedar ordenada,
    // para lo cual deberá insertarse en su lugar desplazando elementos si es necesario.
    // En caso de no haber espacio en la lista correspondiente se indicará mediante un mensaje al usuario.


    listaPrestamo.mostrarPrestamos();

    return 0;
}
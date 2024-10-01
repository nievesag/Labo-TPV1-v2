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

    // menú
    std::cout << "Selecciona algo que hacer (introduzca la letra):" << std::endl;
    std::cout << "a) Mostrar catalogo" << std::endl;
    std::cout << "b) Mostrar prestamos" << std::endl;
    std::cout << "c) Insertar ejemplar" << std::endl;
    std::cout << "d) Prestar ejemplar" << std::endl;
    std::cout << "e) Devolver ejemplar" << std::endl;
    std::cout << "f) Salir" << std::endl;

    char input = ' ';
    std::cin >> input;
    if (input == 'a')
    {
        system("cls");
        catalogo.mostrarCatalogo();
    }
    else if (input == 'b') 
    {
        system("cls");
        listaPrestamo.mostrarPrestamos();
    }
    else if (input == 'c')
    {
        system("cls");

        int tipo = 0;
        std::string nombre = " ";

        std::cout << "De que tipo es tu ejemplar: L) Libros / A) Audiovisual / J) Juegos" << std::endl;
        std::cin >> tipo;
        std::cout << "Inserte el nombre del ejemplar" << std::endl;
        std::cin >> nombre;

        catalogo.insertaEjemplar(tipo, nombre);
    }
    else if (input == 'd')
    {
        system("cls");

        std::cout << "Inserta el codigo del ejemplar a prestar" << std::endl;
        int cod = 0;

        std::cin >> cod;

        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());


    }
    else if (input == 'e')
    {

    }
    else if (input == 'f')
    {

    }
    else if (input == 'g')
    {
        exit(0);
    }

    return 0;
}
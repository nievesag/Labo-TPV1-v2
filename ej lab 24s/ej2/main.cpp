// Nieves Alonso Gilsanz
// Daniel Zhu

#include "Catalogo.h"
#include "ListaPrestamo.h"
#include <windows.h>
#include <iostream>
#include <string>

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

    // mostrar catalogo
    if (input == 'a')
    {
        system("cls");
        catalogo.mostrarCatalogo();
    }

    // mostrar prestamos
    else if (input == 'b') 
    {
        system("cls");
        listaPrestamo.ordenarPrestamos();
        listaPrestamo.mostrarPrestamos();
    }

    // insertar ejemplar (catalogo)
    else if (input == 'c')
    {
        system("cls");

        char tipo = ' ';
        std::string nombre;

        std::cout << "De que tipo es tu ejemplar: L) Libros / A) Audiovisual / J) Juegos" << std::endl;
        std::cin >> tipo;
        std::cout << "Inserte el nombre del ejemplar" << std::endl;
        //std::getline(std::cin, nombre);
        std::cin >> nombre;
        std::cout << "nombre: " << nombre << std::endl;

        catalogo.insertaEjemplar(tipo, nombre);
    }

    // prestar ejemplar
    else if (input == 'd')
    {
        system("cls");

        std::cout << "Inserta el codigo del ejemplar a prestar" << std::endl;
        int cod = 0;
        std::cin >> cod;
        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        Date hoy = Date();

        std::cout << "Inserta tu numero de usuario" << std::endl;
        int u = 0;
        std::cin >> u;

        Prestamo p = Prestamo(e, hoy, u);

        if (listaPrestamo.insertaPrestamo(p))
        {
            std::cout << "Ejemplar prestado" << std::endl;
            p.getEjemplar()->presta();
            listaPrestamo.ordenarPrestamos();
        }
        else 
        {
            std::cout << "Ya se han prestado demasiadas cosas por hoy" << std::endl;
        }
    }

    // devolver ejemplar
    else if (input == 'e')
    {
        system("cls");

        std::cout << "Inserta el codigo del ejemplar a devolver" << std::endl;
        int cod = 0;
        std::cin >> cod;
        Ejemplar* e = catalogo.buscarEjemplar(cod, 0, catalogo.getTam());

        Date hoy = Date();

        std::cout << "Inserta tu numero de usuario" << std::endl;
        int u = 0;
        std::cin >> u;

        Prestamo p = Prestamo(e, hoy, u);

        if (listaPrestamo.devuelvePrestamo(p))
        {
            std::cout << "Ejemplar prestado" << std::endl;
            p.getEjemplar()->devuelve();
            listaPrestamo.ordenarPrestamos();
        }
        else
        {
            std::cout << "No se ha podido devolver" << std::endl;
        }
    }
    else if (input == 'f')
    {
        exit(0);
    }

    return 0;
}
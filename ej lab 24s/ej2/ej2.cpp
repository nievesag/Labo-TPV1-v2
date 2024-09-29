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
    Catalogo* catalogo = new Catalogo;
    ListaPrestamo* prestamo = new ListaPrestamo;

    Ejemplar* listCat = CargaCat();
    Prestamo* listPres = CargaPres();

    catalogo->listCatalogo = listCat;
    prestamo->listPrestamos = listPres;

    catalogo->realCat = listCat.lenght();
}

bool CargaCat(Ejemplar*& ej)
{
    // carga catalogo
    Ejemplar* listCatalogo;
    std::ifstream cat;
    cat.open("catalogo.txt");
    int tamCat = 0;

    if (!cat.is_open()) std::cout << "No se encuentra el fichero" << std::endl;
    else 
    {
        std::cin >> tamCat;
        
         listCatalogo = new Ejemplar[tamCat];

        for (int i = 0; i < tamCat; i++) 
        {
            std::cin >> listCatalogo[i].codigo;
            std::cin >> listCatalogo[i].tipo;
            // leer nombre
        }
    }
    cat.close();

    return listCatalogo;
}

Prestamo* CargaPres()
{
    // carga catalogo
    Prestamo* listPres;
    std::ifstream pres;
    std::string fecha;
    pres.open("prestamos.txt");
    int tamPres = 0;

    if (!pres.is_open()) std::cout << "No se encuentra el fichero" << std::endl;
    else
    {
        std::cin >> tamPres;

        listPres = new Prestamo[tamPres];

        for (int i = 0; i < tamPres; i++)
        {
            std::cin >> listPres[i].codigo;
            std::cin >> fecha;
            std::cin >> listPres[i].user;
        }
    }
    pres.close();

    return listPres;
}

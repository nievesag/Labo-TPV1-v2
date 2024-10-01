#include "ListaPrestamo.h"

#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>

ListaPrestamo::ListaPrestamo()
{

}

ListaPrestamo::ListaPrestamo(std::istream& const e, const Catalogo& c)
{

}

ListaPrestamo::~ListaPrestamo()
{

}

bool ListaPrestamo::leerPrestamos(Catalogo& catalogo)
{
    // abre el archivo coches.txt
    std::fstream prestamoRead("prestamos.txt");

    int c; // codigo del ejemplar
    int u; // usuario del prestamo
    Date fecha; // fecha del prestamo

    // saca el tamaño de la lista de coches
    prestamoRead >> tamArrayPrestamo;

    // crea el array dinamico
    ArrayPrestamo = new Prestamo[tamArrayPrestamo];

    // bucle para leer los datos
    for (int i = 0; i < tamArrayPrestamo; i++)
    {
        prestamoRead >> c; // lee el codigo
        ArrayPrestamo[i].setEjemplar(catalogo.buscarEjemplar(c, 0, catalogo.getTam())); // lo mete
        
        prestamoRead >> fecha; // lee la fecha
        ArrayPrestamo[i].setDate(fecha); // la mete

        prestamoRead >> u; // lee el user
        ArrayPrestamo[i].setUser(u); // lo mete 
    }

    return prestamoRead.is_open(); // true -> archivo prestamos abierto / false -> error  
}

void ListaPrestamo::ordenarPrestamos()
{
    // no me ha dado tiempo :(
    int quedan;
    Date pres;
    Date devol;
    Date* hoy = new Date();

    std::vector<int> aux(tamArrayPrestamo);

    for (int i = 0; i < tamArrayPrestamo; i++)
    {
        pres = ArrayPrestamo[i].getDate();
        devol = pres + (ArrayPrestamo[i].duracionPrestamo((ArrayPrestamo[i].getEjemplar())->getTipo()));
        quedan = (devol.diff(*hoy));

        aux.push_back(quedan);
    }
}

void ListaPrestamo::insertaPrestamo(const Prestamo&)
{

}

void ListaPrestamo::mostrarPrestamos()
{
    int quedan;
    Date pres;
    Date devol;
    Date* hoy = new Date();

    for(int i = 0; i < tamArrayPrestamo; i++)
    {
        pres = ArrayPrestamo[i].getDate();
        devol = ArrayPrestamo[i].getDateDevol();
        std::cout << (devol);
        std::cout << " ";
        quedan = (devol.diff(*hoy));
        std::cout << "(en  " << quedan << " dias)";
        std::cout << " ";
        std::cout << ArrayPrestamo[i].getEjemplar()->getNombre();
        if(quedan < 0)
        {
	        std::cout << " ";
	        std::cout << "(" << abs(quedan)*2 << " dias de penalizacion)";
        }
        std::cout << std::endl;
    }
}
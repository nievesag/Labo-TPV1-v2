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
    delete[] ArrayPrestamo;
    ArrayPrestamo = nullptr;
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
    Prestamo* a = ArrayPrestamo + 8;
    std::sort(ArrayPrestamo, a);
}

void ListaPrestamo::insertaPrestamo(const Prestamo&)
{
    // insertar en el hueco que le corresponde por orden de código
    
}

void ListaPrestamo::devuelvePrestamo()
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

    delete hoy;
}

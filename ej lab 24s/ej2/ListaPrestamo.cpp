#include "ListaPrestamo.h"

#include <algorithm>
#include <fstream>
#include <cmath>
#include <vector>

ListaPrestamo::ListaPrestamo() {}

ListaPrestamo::ListaPrestamo(std::istream& const e, const Catalogo& c) {}

ListaPrestamo::~ListaPrestamo()
{
    delete[] ArrayPrestamo;
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
    ArrayPrestamo = new Prestamo[maxArrayPrestamo];

    int i = 0;
    while (i < tamArrayPrestamo && (prestamoRead >> c >> fecha >> u)) //mientras pueda seguir leyendo c >> fecha >> u no se sale
    {
        ArrayPrestamo[i].setEjemplar(catalogo.buscarEjemplar(c, 0, catalogo.getTam())); 
        ArrayPrestamo[i].setDate(fecha); 
        ArrayPrestamo[i].setUser(u); 
        contPrestamos++;
        i++; 
    }

    return prestamoRead.is_open(); // true -> archivo prestamos abierto / false -> error  
}

void ListaPrestamo::ordenarPrestamos()
{
    Prestamo* a = ArrayPrestamo + contPrestamos;
    std::sort(ArrayPrestamo, a);
}

bool ListaPrestamo::insertaPrestamo(const Prestamo& p)
{
    if (contPrestamos < tamArrayPrestamo) 
    {
        for (int i = contPrestamos-1; i > 0; i--) 
        {
            if (p.getDateDevol() < ArrayPrestamo[i].getDateDevol())
            {
                ArrayPrestamo[i+1] = ArrayPrestamo[i];
                ArrayPrestamo[i] = p; 
            }
            else 
            {
                ArrayPrestamo[i + 1] = p;
            }
        }

        contPrestamos++;

        // abre el archivo 
        std::ofstream prestamosWrite("prestamos.txt", std::ios::app);
        int user = p.getUser();
        prestamosWrite << p.getEjemplar()->getCodigo() << " " << p.getDateDevol() << " " << user << std::endl;
        prestamosWrite.close(); // close the file

        return true;
    }

    return false;
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

    for(int i = 0; i < contPrestamos; i++)
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
        std::cout << contPrestamos;
    }

    delete hoy;
}
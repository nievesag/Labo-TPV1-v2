#include "Catalogo.h"

#include <fstream>
#include <iostream>

Catalogo::Catalogo()
{

}

Catalogo::Catalogo(std::istream&)
{

}

Catalogo::~Catalogo()
{
    delete[] ArrayCatalogo;
}

bool Catalogo::leerCatalogo()
{
    // abre el archivo coches.txt
    std::fstream catalogoRead("catalogo.txt");

    int c; // codigo del ejemplar
    char tc; // tipo del ejemplar, char
    int ti; 
    std::string n; // nombre del ejemplar

    // saca el tamaño de la lista de coches
    catalogoRead >> tamArrayCatalogo;

    // crea el array dinamico
    ArrayCatalogo = new Ejemplar[tamArrayCatalogo];

    // bucle para leer los datos
    for (int i = 0; i < tamArrayCatalogo; i++)
    {
        catalogoRead >> c; // lee el codigo
        ArrayCatalogo[i].setCodigo(c); // lo mete

        catalogoRead >> tc; // lee el tipo

        if(tc == 'L') // libros
        {
            ti = 0;
        }
        else if (tc == 'A') // audiovisual
        {
            ti = 1;
        }
        else // juegos
        {
            ti = 2;
        }

        ArrayCatalogo[i].setTipo(ti); // lo mete 

        std::getline(catalogoRead, n); // lee el nombre
        ArrayCatalogo[i].setNombre(n); // lo mete

        contCatalogo++;
    }

    return catalogoRead.is_open(); // true -> archivo catalogo abierto / false -> error
}

Ejemplar* Catalogo::buscarEjemplar(int cod, int ini, int fin) const
{
    int elems = fin - ini;

    if (elems == 0) return nullptr; // vacio
    if (elems == 1) return getEjemplar(ini);

    int mit = (ini + fin) / 2;

    if (cod >= getEjemplar(mit)->getCodigo()) // busca derecha
    {
        return buscarEjemplar(cod, mit, fin);
    }
    if (cod < getEjemplar(mit)->getCodigo()) // busca izq
    {
        return buscarEjemplar(cod, ini, mit);
    }

    return nullptr;
}

void Catalogo::insertaEjemplar(char tipo, std::string nombre)
{
    if (contCatalogo < maxArrayCatalogo) 
    {
        // codigo -> ultimo ejemplar +1
        int cod = ArrayCatalogo[tamArrayCatalogo - 1].getCodigo() + 1;

        int tamAux = tamArrayCatalogo + 1;
	    Ejemplar* aux = new Ejemplar[tamAux];

        std::copy(ArrayCatalogo, ArrayCatalogo + 1, aux);

        delete[] ArrayCatalogo;

        ArrayCatalogo = aux;
        tamArrayCatalogo = tamAux;

        // meter en el catalogo
        ArrayCatalogo[tamArrayCatalogo - 1].setCodigo(cod);

        int t = 0;
        if (tipo == 'L') // libros
        {
            t = 0;
        }
        else if (tipo == 'A') // audiovisual
        {
            t = 1;
        }
        else // juegos
        {
            t = 2;
        }

        ArrayCatalogo[tamArrayCatalogo - 1].setTipo(t);
        ArrayCatalogo[tamArrayCatalogo - 1].setNombre(nombre);

        contCatalogo++;

        std::ofstream catalogoWrite("catalogo.txt", std::ios::app);
        catalogoWrite << cod << " " << tipo << " " << ArrayCatalogo[tamArrayCatalogo - 1].getNombre() << std::endl;
        catalogoWrite.close(); // close the file
    }
}

void Catalogo::mostrarCatalogo()
{
    for (int i = 0; i < tamArrayCatalogo; i++)
    {
        std::cout << ArrayCatalogo[i].getCodigo();
        std::cout << " ";
        if (ArrayCatalogo[i].getTipo() == 0) { std::cout << "L"; }
        else if (ArrayCatalogo[i].getTipo() == 1) { std::cout << "A"; }
        else { std::cout << "J"; }
        std::cout << " ";
        std::cout << ArrayCatalogo[i].getNombre();
        std::cout << std::endl;
    }
}
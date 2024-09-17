// hoja 1
// Nieves Alonso Gilsanz
// Ariadna Alicia Ruiz Castillo

#include <iostream>

int main()
{
    // ej 1
    /*
    int x = 5, y = 12, z;
    int* p1, *p2, *p3;
    p1 = &x;
    p2 = &y;
    z = *p1 * *p2;
    p3 = &z;
    (*p3)++;
    p1 = p3;
    std::cout << *p1 << " " << *p2 << " " << *p3;
    */

    // muestra: 61 12 61

    // ej 2
    /*
    int dato = 5;
    int *p1, *p2; // p2 debe ser puntero
    p1 = &dato;
    p2 = p1; // solo puedes igualar punteros
    std::cout << *p2;
    */

    // ej 3
    /*
    double d = 5.4, e = 1.2, f = 0.9;
    double *p1, *p2, *p3;
    p1 = &d;
    (*p1) = (*p1) + 3;
    p2 = &e;
    (*p3) = (*p1) + (*p2); // p3 no apunta a nada, abria que hacer que apuntase a f, por ejemlo
    std::cout << *p1 << " " << *p2 << " " << *p3;
    */

    // ej 4
    /*
    Registro r1;
    Registro* pr = new Registro;
    // los registros r1 y *pr toman valor

    double cotiza;
    int años;
    func(r1, cotiza, años);
    func(*pr, cotiza, años);

    func2(&r1, &cotiza, &años);
    func2(pr, &cotiza, &años);
    */

    // ej 5
    /*
    Registro r1;
    Registro* pr = nullptr;
    // los registros r1 y *pr toman valor

    double cotiza; 
    int años;

    r1 = *crearNuevoReg();
    pr = crearNuevoReg();

    crearNuevoReg2(r1);
    crearNuevoReg2(pr);

    func(r1, cotiza, años);
    func(*pr, cotiza, años);
    */

    // ej 6
    /*
    int x = 5, y = 8;
    int* px = &x, * py = &y, * p;
    int** ppx = &px, ** ppy = &py, ** pp;
    p = px;
    px = py;
    py = p;
    pp = ppx;
    ppx = ppy;
    ppy = pp;
    std::cout << **ppx << " " << **ppy;
    */

    // se muestra: 5 8

    // ej 7
    // a)
    /*
    int* p;
    p = new int;
    *p = 100;
    std::cout << *p;
    // escribe: 100

    p = new int; // no puedes reasignar el puntero, da problemas, p no puede apuntar a dos cosas a la vez, habría que eliminar el primero
    *p = 32;
    std::cout << *p;
    */

    // b)
    /*
    int *p, *q; // 1) habría que hacer a q puntero, 2) si no lo haces puntero
    p = new int;
    q = p; // 1) son de tipos distintos no puedes, 2) hay que poner * a p
    *p = 42;
    std::cout << q; // 2) quitar el asterisco
    // escribe: 42 (si lo arreglas)

    delete q; // 2) no podrias hacer delete si no es puntero
    std::cout << *p;
    */
    // escribe: 42
}

/*
struct Registro 
{
    std::string nombre;
    double sueldo;
    int edad;
};
*/

// ej 4
/*
void func(Registro& reg, double& irpf, int& edad)
{
    const double TIPO = 0.18;
    reg.edad++;
    irpf = reg.sueldo * TIPO;
    edad = reg.edad;
}

void func2(Registro *reg, double *irpf, int *edad)
{
    const double TIPO = 0.18;
    reg->edad++;
    *irpf = reg->sueldo * TIPO;
    *edad = reg->edad;
}
*/

// ej 5
/*
Registro* crearNuevoReg() 
{
    Registro* preg = new Registro; // el registro *preg toma valor
    return preg;
}

void crearNuevoReg2(Registro* &preg)
{
    Registro* preg = new Registro; // el registro *preg toma valor
}
*/

// ej 6
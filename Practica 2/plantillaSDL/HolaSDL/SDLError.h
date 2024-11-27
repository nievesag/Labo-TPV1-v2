#ifndef SDLERROR_H
#define SDLERROR_H

#include <string>

#include "GameError.h"

class SDLError : public GameError
{
    // para todos los errores relacionados con la inicializacion y uso de SDL
public:
    // para obtener un mensaje especifico sobre el error de SDL, se almacenara en la excepcion
    SDLError(const std::string& message);
};

#endif
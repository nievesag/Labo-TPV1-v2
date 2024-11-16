#ifndef FILENOTFOUNDERROR_H
#define FILENOTFOUNDERROR_H

#include "GameError.h"

class FileNotFoundError : public GameError
{
	// para los errores provocados al no encontrarse un fichero que el programa trata de abrir
	// el mensaje del error debe incluir el nombre del fichero que da error
public:
	FileNotFoundError(const std::string& message);
};

#endif
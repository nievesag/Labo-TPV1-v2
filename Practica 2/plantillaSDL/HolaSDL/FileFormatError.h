#ifndef FILEFORMATERROR_H
#define FILEFORMATERROR_H

#include "GameError.h"

class FileFormatError : public GameError
{
	// para los errores provocados en la lectura de los archivos de datos del juego (mapas y partidas guardadas)
	// la excepcion debe almacenar y mostrar el nombre de archivo y el numero de linea del error junto con el mensaje
public:
	FileFormatError(const std::string& message);
};

#endif
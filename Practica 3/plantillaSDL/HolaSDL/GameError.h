#ifndef INVADERSERROR_H
#define INVADERSERROR_H

#include <stdexcept>

class GameError : public std::logic_error
{
    // SUPERCLASE DE LAS DEMAS EXCEPCIONES
	// Reutiliza el constructor y metodo what de logic_error para almacenamiento y uso del mensaje de la excepcion
protected:
    std::string errorMessage;

public:
    GameError(const std::string& message);
    char const* what() const override;
};

#endif
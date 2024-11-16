#include "GameError.h"

GameError::GameError(const std::string& message) : logic_error(message)
{
	errorMessage = message;
}

char const* GameError::what() const
{
	return errorMessage.c_str(); // devuelve el mensaje de error en const string
}
#include "SDLError.h"

SDLError::SDLError(const std::string& message) : GameError(message)
{
	errorMessage = message;
}
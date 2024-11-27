#include "FileNotFoundError.h"

FileNotFoundError::FileNotFoundError(const std::string& message) : GameError(message)
{
	errorMessage = message;
}
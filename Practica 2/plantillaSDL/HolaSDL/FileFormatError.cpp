#include "FileFormatError.h"

FileFormatError::FileFormatError(const std::string& message) : GameError(message)
{
	errorMessage = message;
}
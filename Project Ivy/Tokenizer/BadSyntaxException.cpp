#include "BadSyntaxException.h"


BadSyntaxException::BadSyntaxException(int lineNumber, int linePosition)
{
	this->exceptionMessage = "Bad syntax on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition);
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
}

BadSyntaxException::~BadSyntaxException()
{
}
 
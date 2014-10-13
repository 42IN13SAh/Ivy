#include "BadSyntaxException.h"


BadSyntaxException::BadSyntaxException(std::string syntaxDescription, int lineNumber, int linePosition)
{
	this->exceptionMessage = "BadSyntax, On linenumber: " + std::to_string(lineNumber) +  " and lineposition: " + std::to_string(linePosition);
}

BadSyntaxException::~BadSyntaxException()
{
}
 
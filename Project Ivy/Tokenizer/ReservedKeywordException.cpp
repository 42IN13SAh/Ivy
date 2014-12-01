#include "ReservedKeywordException.h"


ReservedKeywordException::ReservedKeywordException(std::string token, int lineNumber, int linePosition) : BadSyntaxException(lineNumber, linePosition)
{
	this->exceptionMessage = "\"" + token + "\" is a reserved keyword. You may not use this name. Error on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition);
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
	this->token = token;
}


ReservedKeywordException::~ReservedKeywordException()
{
}

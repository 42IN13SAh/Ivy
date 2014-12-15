#include "ReservedKeywordException.h"


ReservedKeywordException::ReservedKeywordException(int lineNumber, int linePosition, std::string token) : BaseException(lineNumber, linePosition)
{
	exceptionMessage = "\"" + token + "\" is a reserved keyword. You may not use this name. Error on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition);
}


ReservedKeywordException::~ReservedKeywordException()
{
}
#include "BadSyntaxException.h"


BadSyntaxException::BadSyntaxException(int lineNumber, int linePosition, std::vector<std::string> followUps, std::string token) : BaseException(lineNumber, linePosition)
{
	exceptionMessage = "Bad syntax on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition) + " after '" + token + "' possible followups: '" + VectorUtils::JoinVector(followUps, "' '") + "'";
}

BadSyntaxException::~BadSyntaxException()
{
}
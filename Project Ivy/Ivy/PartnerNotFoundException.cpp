#include "PartnerNotFoundException.h"


PartnerNotFoundException::PartnerNotFoundException(std::string token, int lineNumber, int linePosition) : BadSyntaxException(lineNumber, linePosition)
{
	this->exceptionMessage = "Partner not found for token \"" + token + "\" on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition);
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
	this->token = token;
}


PartnerNotFoundException::~PartnerNotFoundException()
{
}
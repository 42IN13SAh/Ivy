#include "PartnerNotFoundException.h"


PartnerNotFoundException::PartnerNotFoundException(int lineNumber, int linePosition, std::vector<std::string> followUps, std::string token) : BaseException(lineNumber, linePosition)
{
	exceptionMessage = "Partner not found for token \"" + token + "\" on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition) + ", possible partners: '" + VectorUtils::JoinVector(followUps, "' '") + "'";
	//this->token = token;
}


PartnerNotFoundException::~PartnerNotFoundException()
{
}
#pragma once
#include <string>
#include <vector>
#include "BadMatchException.h"
#include "VectorUtils.h"

class PartnerNotFoundException : public BadMatchException
{
public:
	PartnerNotFoundException(int lineNumber, int linePosition, int sid, const std::string& token) : BadMatchException(lineNumber, linePosition, sid) {
		exceptionMessage = "Partner not found for token \"" + token + "\" on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition) + ", possible partners: '" + VectorUtils::JoinVector(getPartners(sid), "' '") + "'";
	}
	virtual ~PartnerNotFoundException() {}
};

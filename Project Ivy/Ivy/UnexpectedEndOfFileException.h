#ifndef UNENDOFFILEEXCEPTION_H
#define UNENDOFFILEEXCEPTION_H

#include <string>
#include "BadMatchException.h"
#include "VectorUtils.h"

class UnexpectedEndOfFileException : public BadMatchException
{
public:
	UnexpectedEndOfFileException(int lnr, int lps, int sid, std::string token) : BadMatchException(lnr, lps, sid) {
		exceptionMessage = "Unexpected end of file after '" + token + "' on line number " + std::to_string(lnr) + " and lineposition " + std::to_string(lps) + " possible followups: '" + VectorUtils::JoinVector(getFollowUps(sid), "' '") + "'";
	}
	virtual ~UnexpectedEndOfFileException() {}
};


#endif
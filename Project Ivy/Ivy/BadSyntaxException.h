#pragma once
#include <string>
#include <vector>
#include "BadMatchException.h"
#include "VectorUtils.h"

class BadSyntaxException : public BadMatchException
{
public:

	BadSyntaxException(int lnr, int lps, int sid, const std::string& token) : BadMatchException(lnr, lps, sid) {
		exceptionMessage = "Bad syntax on linenumber " + std::to_string(lnr) + " and lineposition " + std::to_string(lps) + " after '" + token + "' possible followups: '" + VectorUtils::JoinVector(getFollowUps(sid), "' '") + "'";
	}
	~BadSyntaxException() {}
};

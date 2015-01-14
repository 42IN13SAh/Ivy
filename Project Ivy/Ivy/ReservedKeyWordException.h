#pragma once
#include <string>
#include "BaseException.h"

class ReservedKeywordException : public BaseException
{
public:
	ReservedKeywordException(int lineNumber, int linePosition, const std::string& token) : BaseException(lineNumber, linePosition) {
		exceptionMessage = "\"" + token + "\" is a reserved keyword. You may not use this name. Error on linenumber " + std::to_string(lineNumber) + " and lineposition " + std::to_string(linePosition);
	}
	virtual ~ReservedKeywordException() {}
};

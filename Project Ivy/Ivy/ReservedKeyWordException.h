#pragma once
#include <string>
#include "BaseException.h"
class ReservedKeywordException : public BaseException
{
public:
	ReservedKeywordException(int lineNumber, int linePosition, std::string token);
	virtual ~ReservedKeywordException();
};

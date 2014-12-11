#pragma once
#include "BadSyntaxException.h"
class ReservedKeywordException :
	public BadSyntaxException
{
public:
	ReservedKeywordException(std::string token, int lineNumber, int linePosition);
	virtual ~ReservedKeywordException();
};

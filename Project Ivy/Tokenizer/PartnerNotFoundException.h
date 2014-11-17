#pragma once
#include "BadSyntaxException.h"
class PartnerNotFoundException :
	public BadSyntaxException
{
public:
	PartnerNotFoundException(std::string token, int lineNumber, int linePosition);
	virtual ~PartnerNotFoundException();
};


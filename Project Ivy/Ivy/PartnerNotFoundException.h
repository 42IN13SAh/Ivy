#pragma once
#include <string>
#include <vector>
#include "BaseException.h"
#include "VectorUtils.h"
class PartnerNotFoundException : public BaseException
{
public:
	PartnerNotFoundException(int lineNumber, int linePosition, std::vector<std::string> followUps, std::string token);
	virtual ~PartnerNotFoundException();
};

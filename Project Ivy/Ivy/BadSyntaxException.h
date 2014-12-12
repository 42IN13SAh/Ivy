#pragma once
#include <string>
#include <vector>
#include "BaseException.h"
#include "VectorUtils.h"
class BadSyntaxException : public BaseException
{
public:

	BadSyntaxException(int lnr, int lps, std::vector<std::string> followUps, std::string);
	~BadSyntaxException();
};

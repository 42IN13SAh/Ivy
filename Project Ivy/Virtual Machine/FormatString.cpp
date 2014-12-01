#include "FormatString.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("formatString", FormatString, 100);

void FormatString::Execute(std::vector<boost::any> arglist)
{

}

boost::any FormatString::GetResult()
{
	return Result;
}

FormatString::~FormatString()
{
}

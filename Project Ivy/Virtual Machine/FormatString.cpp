#include "FormatString.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("formatString", FormatString);

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

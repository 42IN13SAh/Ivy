#include "Date.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("date", Date);

void Date::Execute(std::vector<boost::any> arglist)
{

}

boost::any Date::GetResult()
{
	return Result;
}

Date::~Date()
{
}

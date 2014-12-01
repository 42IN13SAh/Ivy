#include "Time.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("time", Time, 0);

void Time::Execute(std::vector<boost::any> arglist)
{

}

boost::any Time::GetResult()
{
	return Result;
}

Time::~Time()
{
}

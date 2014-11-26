#include "Time.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("time", Time);

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

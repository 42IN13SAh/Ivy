#include "Log.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("log", Log, 1);

void Log::Execute(std::vector<boost::any> arglist)
{

}

boost::any Log::GetResult()
{
	return Result;
}

Log::~Log()
{
}

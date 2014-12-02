#include "Log.h"

void Log::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = log(a);
}

boost::any Log::GetResult()
{
	return Result;
}

Log::~Log()
{
}

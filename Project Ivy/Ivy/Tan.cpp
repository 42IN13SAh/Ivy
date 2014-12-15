#include "Tan.h"

void Tan::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = std::tan(a);
}

boost::any Tan::GetResult()
{
	return Result;
}

Tan::~Tan()
{
}

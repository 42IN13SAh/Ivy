#include "Sin.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("sin", Sin);

void Sin::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = sin(a);
}

boost::any Sin::GetResult()
{
	return Result;
}

Sin::~Sin()
{
}

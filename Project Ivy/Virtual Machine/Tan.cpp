#include "Tan.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("tan", Tan);

void Tan::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = tan(a);
}

boost::any Tan::GetResult()
{
	return Result;
}

Tan::~Tan()
{
}

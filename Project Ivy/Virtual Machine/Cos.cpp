#include "Cos.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("cos", Cos, 1);

void Cos::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = cos(a);
}

boost::any Cos::GetResult()
{
	return Result;
}

Cos::~Cos()
{
}

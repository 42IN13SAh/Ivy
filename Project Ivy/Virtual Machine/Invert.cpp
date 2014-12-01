#include "Invert.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("invert", Invert);

void Invert::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = -a;
}

boost::any Invert::GetResult()
{
	return Result;
}

Invert::~Invert()
{
}

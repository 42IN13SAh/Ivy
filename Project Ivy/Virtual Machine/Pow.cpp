#include "Pow.h"
#include <math.h>
#include <iostream>
#include <string>
#include "InternalFunctionFactory.h"

REGISTER_CLASS("pow", Pow);

void Pow::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	double b = boost::any_cast<double>(arglist[1]);
	Result = pow(a, b);
	std::cout << boost::any_cast<double>(Result);
}

boost::any Pow::GetResult()
{
	return Result;
}

Pow::~Pow()
{
}

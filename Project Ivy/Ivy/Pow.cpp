#include "Pow.h"

void Pow::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	double b = boost::any_cast<double>(arglist[1]);
	Result = std::pow(a, b);
}

boost::any Pow::GetResult()
{
	return Result;
}

Pow::~Pow()
{
}

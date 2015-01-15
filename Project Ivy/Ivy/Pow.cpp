#include "Pow.h"

void Pow::Execute(std::vector<boost::any> arglist)
{
	double a = Cast::cast<double>(arglist[0]);
	double b = Cast::cast<double>(arglist[1]);
	Result = std::pow(a, b);
}

boost::any Pow::GetResult()
{
	return Result;
}

Pow::~Pow()
{
}

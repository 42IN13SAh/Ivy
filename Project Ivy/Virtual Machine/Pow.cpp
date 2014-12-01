#include "Pow.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("pow", Pow, 2);

void Pow::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	double b = boost::any_cast<double>(arglist[1]);
	double tempa = a;
	for (int i = 0; i < b; i++)
		a = a * tempa;
	Result = a;
}

boost::any Pow::GetResult()
{
	return Result;
}

Pow::~Pow()
{
}

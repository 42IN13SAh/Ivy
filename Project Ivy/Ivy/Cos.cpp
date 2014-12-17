#include "Cos.h"

void Cos::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = std::cos(a);
}

boost::any Cos::GetResult()
{
	return Result;
}

Cos::~Cos()
{
}

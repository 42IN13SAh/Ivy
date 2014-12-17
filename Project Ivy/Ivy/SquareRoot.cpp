#include "SquareRoot.h"

void SquareRoot::Execute(std::vector<boost::any> arglist)
{
	double x = boost::any_cast<double>(arglist[0]);
	Result = std::sqrt(x);
}

boost::any SquareRoot::GetResult()
{
	return Result;
}

SquareRoot::~SquareRoot()
{
}

#include "SquareRoot.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("squareRoot", SquareRoot);

void SquareRoot::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	Result = sqrt(a);
}

boost::any SquareRoot::GetResult()
{
	return Result;
}

SquareRoot::~SquareRoot()
{
}

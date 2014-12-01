#include "SquareRoot.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("squareRoot", SquareRoot, 1);

void SquareRoot::Execute(std::vector<boost::any> arglist)
{

}

boost::any SquareRoot::GetResult()
{
	return Result;
}

SquareRoot::~SquareRoot()
{
}

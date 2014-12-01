#include "Tan.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("tan", Tan, 1);

void Tan::Execute(std::vector<boost::any> arglist)
{

}

boost::any Tan::GetResult()
{
	return Result;
}

Tan::~Tan()
{
}

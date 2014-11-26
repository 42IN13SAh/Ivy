#include "Sin.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("sin", Sin);

void Sin::Execute(std::vector<boost::any> arglist)
{

}

boost::any Sin::GetResult()
{
	return Result;
}

Sin::~Sin()
{
}

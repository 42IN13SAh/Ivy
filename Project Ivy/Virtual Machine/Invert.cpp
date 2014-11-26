#include "Invert.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("invert", Invert, 1);

void Invert::Execute(std::vector<boost::any> arglist)
{

}

boost::any Invert::GetResult()
{
	return Result;
}

Invert::~Invert()
{
}

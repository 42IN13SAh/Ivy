#include "Invert.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("invert", Invert);

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

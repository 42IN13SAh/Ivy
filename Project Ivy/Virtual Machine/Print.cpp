#include "Print.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("print", Print);

void Print::Execute(std::vector<boost::any> arglist)
{

}

boost::any Print::GetResult()
{
	return Result;
}

Print::~Print()
{
}

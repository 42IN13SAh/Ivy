#include "Print.h"
#include "InternalFunctionFactory.h"
#include <string>
#include <iostream>

REGISTER_CLASS("print", Print);

void Print::Execute(std::vector<boost::any> arglist)
{
	std::string a = boost::any_cast<std::string>(arglist[0]);
	std::cout << a;
}

boost::any Print::GetResult()
{
	return Result;
}

Print::~Print()
{
}

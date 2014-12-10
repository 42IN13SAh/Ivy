#include <string>
#include <iostream>
#include "Print.h"

void Print::Execute(std::vector<boost::any> arglist)
{
	std::string r;
	try {
		r = std::to_string(boost::any_cast<double>(arglist[0]));
	}
	catch (std::exception e) {
		r = boost::any_cast<std::string>(arglist[0]);
	}
	std::cout << r;
}

boost::any Print::GetResult()
{
	return Result;
}

Print::~Print()
{
}

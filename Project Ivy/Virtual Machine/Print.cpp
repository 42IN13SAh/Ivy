#include "Print.h"
#include <string>
#include <iostream>

void Print::Execute(std::vector<boost::any> arglist)
{
	std::string r;
	try {
		r = std::to_string(boost::any_cast<double>(arglist[0]));
	}
	catch (std::exception e) {
		r = boost::any_cast<std::string>(arglist[0]);
	}
	std::cout << r << std::endl;
}

boost::any Print::GetResult()
{
	return Result;
}

Print::~Print()
{
}

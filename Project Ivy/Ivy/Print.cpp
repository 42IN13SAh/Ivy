#include "Print.h"

void Print::Execute(std::vector<boost::any> arglist)
{
	if (string(arglist[0]) || number(arglist[0]) || boolean(arglist[0])){
		std::cout << *stringToPrint;
	}
}

boost::any Print::GetResult()
{
	return Result;
}

Print::~Print()
{
	delete stringToPrint;
}

bool Print::number(boost::any value)
{
	try{
		double a = boost::any_cast<double>(value);
		stringToPrint = new std::string(std::to_string(a));
		return true;
	}
	catch (std::exception& e){
		return false;
	}
}

bool Print::boolean(boost::any value)
{
	try{
		bool a = boost::any_cast<bool>(value);
		if (a){
			stringToPrint = new std::string("true");
		}
		else{
			stringToPrint = new std::string("false");
		}
		return true;
	}
	catch (std::exception& e){
		return false;
	}
}

bool Print::string(boost::any value)
{
	try{
		stringToPrint = new std::string(boost::any_cast<std::string>(value));
		return true;
	}
	catch (std::exception& e){
		return false;
	}
}
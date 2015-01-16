#include "Invert.h"

void Invert::Execute(std::vector<boost::any> arglist)
{
	if (number(arglist[0])){
		return;
	}
	if (boolean(arglist[0])){
		return;
	}
	if (string(arglist[0])){
		return;
	}
}

boost::any Invert::GetResult()
{
	return Result;
}

Invert::~Invert()
{
}

bool Invert::number(boost::any value)
{
	try{
		double a = Cast::cast<double>(value);
		Result = -a;
		return true;
	}
	catch (std::exception& e){
		return false;
	}
}

bool Invert::boolean(boost::any value)
{
	try{
		bool a = Cast::cast<bool>(value);
		Result = !a;
		return true;
	}
	catch (std::exception& e){
		return false;
	}
}

bool Invert::string(boost::any value)
{
	try{
		std::string a = Cast::cast<std::string>(value);
		std::reverse(a.begin(), a.end());
		Result = a;
		return true;
	}
	catch (std::exception& e){
		return false;
	}
}
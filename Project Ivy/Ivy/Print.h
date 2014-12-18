#pragma once
#include "IInternalFunction.h" 
#include <string>
#include <iostream>

class Print : public IInternalFunction
{
public:
	~Print();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
	std::string stringToPrint;
	bool number(boost::any value);
	bool string(boost::any value);
	bool boolean(boost::any value);
};


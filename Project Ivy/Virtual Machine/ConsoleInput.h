#pragma once
#include "IInternalFunction.h" 

class ConsoleInput : public IInternalFunction
{
public:
	~ConsoleInput();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


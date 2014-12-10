#pragma once
#include "IInternalFunction.h" 

class Sin : public IInternalFunction
{
public:
	~Sin();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


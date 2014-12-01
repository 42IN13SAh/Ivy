#pragma once
#include "IInternalFunction.h"

class Date : public IInternalFunction
{
public:
	~Date();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


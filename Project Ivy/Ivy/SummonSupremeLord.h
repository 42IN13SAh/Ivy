#pragma once
#include "IInternalFunction.h"
#include <string>
#include <iostream>

class SummonSupremeLord : public IInternalFunction
{
public:
	~SummonSupremeLord();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


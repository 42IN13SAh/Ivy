#pragma once
#include "IInternalFunction.h"
#include <string>
#include <iostream>

class SummonSupremeCommander : public IInternalFunction
{
public:
	~SummonSupremeCommander();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


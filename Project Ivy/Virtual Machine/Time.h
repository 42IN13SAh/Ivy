#pragma once
#include "IInternalFunction.h" 

class Time : public IInternalFunction
{
public:
	~Time();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


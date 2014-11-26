#pragma once
#include "IInternalFunction.h" 

class Random : public IInternalFunction
{
public:
	~Random();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


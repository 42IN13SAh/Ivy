#pragma once
#include "IInternalFunction.h" 

class Invert : public IInternalFunction
{
public:
	~Invert();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


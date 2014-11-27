#pragma once
#include "IInternalFunction.h" 

class SquareRoot : public IInternalFunction
{
public:
	~SquareRoot();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


#pragma once
#include "IInternalFunction.h" 

class Cos : public IInternalFunction
{
public:
	~Cos();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


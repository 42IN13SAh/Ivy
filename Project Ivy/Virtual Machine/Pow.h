#pragma once
#include "IInternalFunction.h" 

class Pow : public IInternalFunction
{
public:
	~Pow();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


#pragma once
#include "IInternalFunction.h" 

class Tan : public IInternalFunction
{
public:
	~Tan();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


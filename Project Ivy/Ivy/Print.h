#pragma once
#include "IInternalFunction.h" 

class Print : public IInternalFunction
{
public:
	~Print();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


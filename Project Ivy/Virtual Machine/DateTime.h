#pragma once
#include "IInternalFunction.h" 

class DateTime : public IInternalFunction
{
public:
	~DateTime();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


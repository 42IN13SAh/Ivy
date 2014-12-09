#pragma once
#include "IInternalFunction.h" 

class Log : public IInternalFunction
{
public:
	~Log();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


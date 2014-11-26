#pragma once
#include "IInternalFunction.h" 

class FormatString : public IInternalFunction
{
public:
	~FormatString();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


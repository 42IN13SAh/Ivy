#pragma once
#include "IinternalFunction.h" 

class Pow : public IinternalFunction
{
public:
	~Pow();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


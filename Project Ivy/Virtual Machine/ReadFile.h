#pragma once
#include "IInternalFunction.h" 

class ReadFile : public IInternalFunction
{
public:
	~ReadFile();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


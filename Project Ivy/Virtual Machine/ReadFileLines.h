#pragma once
#include "IInternalFunction.h" 

class ReadFileLines : public IInternalFunction
{
public:
	~ReadFileLines();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


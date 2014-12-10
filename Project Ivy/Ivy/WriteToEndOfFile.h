#pragma once
#include "IInternalFunction.h" 

class WriteToEndOfFile : public IInternalFunction
{
public:
	~WriteToEndOfFile();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


#pragma once
#include <vector>
#include <string>
#include "IInternalFunction.h"
class WriteToFile : public IInternalFunction
{
public:
	~WriteToFile();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


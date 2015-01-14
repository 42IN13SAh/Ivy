#pragma once
#include <vector>
#include "IInternalFunction.h"
class RandomWithRange : public IInternalFunction
{
public:
	~RandomWithRange();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


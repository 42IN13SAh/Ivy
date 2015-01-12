#pragma once
#include <vector>
#include "IInternalFunction.h"
#include "RandomWithPara.h"
class RandomWithPara : public IInternalFunction
{
public:
	~RandomWithPara();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
};


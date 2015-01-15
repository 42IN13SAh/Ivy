#pragma once
#include <vector>
#include <boost\any.hpp>
#include "Cast.h"

class IInternalFunction
{
public:
	virtual void Execute(std::vector<boost::any> arglist) = 0;
	virtual boost::any GetResult() = 0;
	virtual ~IInternalFunction(){}
};

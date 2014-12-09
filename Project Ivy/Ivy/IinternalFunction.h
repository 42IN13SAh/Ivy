#pragma once
#include <vector>
#include <boost\any.hpp>

class IInternalFunction
{
public:
	virtual void Execute(std::vector<boost::any> arglist) = 0;
	virtual boost::any GetResult() = 0;
};

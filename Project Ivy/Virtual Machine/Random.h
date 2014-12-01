#pragma once
#include "IInternalFunction.h" 
#include <random>

class Random : public IInternalFunction
{
public:
	~Random();
	virtual void Execute(std::vector<boost::any> arglist);
	virtual boost::any GetResult();
private:
	boost::any Result;
	static std::random_device rd;
	static std::mt19937 mt;
};


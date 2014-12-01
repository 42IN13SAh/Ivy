#include "Random.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("random", Random, 2);

void Random::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	double b = boost::any_cast<double>(arglist[1]);
	std::uniform_int_distribution<int> dist(a, b);
	Result = dist(mt);
}

boost::any Random::GetResult()
{
	return Result;
}

Random::~Random()
{
}

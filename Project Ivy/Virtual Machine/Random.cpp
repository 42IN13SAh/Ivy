#include "Random.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("random", Random);
std::random_device Random::rd;
std::mt19937 Random::mt(rd());

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

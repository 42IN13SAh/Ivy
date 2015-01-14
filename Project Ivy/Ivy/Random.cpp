#include <random>
#include "Random.h"

void Random::Execute(std::vector<boost::any> arglist)
{
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	Result = (double) generator();
}

boost::any Random::GetResult()
{
	return Result;
}

Random::~Random()
{
}

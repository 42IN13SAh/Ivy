#include "Random.h"
#include <random>
#include <iostream>

void Random::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	double b = boost::any_cast<double>(arglist[1]);

	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<> distribute(a, b);

	double result = distribute(generator);
	Result = result;
}

boost::any Random::GetResult()
{
	return Result;
}

Random::~Random()
{
}

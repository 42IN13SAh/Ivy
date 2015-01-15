#include <random>
#include "RandomWithRange.h"


RandomWithRange::~RandomWithRange()
{
}

boost::any RandomWithRange::GetResult()
{
	return Result;
}

void RandomWithRange::Execute(std::vector<boost::any> arglist)
{
	double a = Cast::cast<double>(arglist[0]);
	double b = Cast::cast<double>(arglist[1]);

	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<> distribute(a, b);

	double result = distribute(generator);
	Result = result;
}
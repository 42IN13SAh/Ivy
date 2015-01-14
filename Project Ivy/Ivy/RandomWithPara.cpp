#include <random>
#include "RandomWithPara.h"

RandomWithPara::~RandomWithPara()
{
}

void RandomWithPara::Execute(std::vector<boost::any> arglist)
{
	double a = boost::any_cast<double>(arglist[0]);
	std::random_device randomDevice;
	std::mt19937 generator(randomDevice());
	std::uniform_int_distribution<> distribute(0, a);
	Result = (double)distribute(generator);
}

boost::any RandomWithPara::GetResult()
{
	return Result;
}


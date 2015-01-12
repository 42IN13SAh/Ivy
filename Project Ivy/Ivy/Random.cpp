#include "Random.h"
#include "Time.h"
void Random::Execute(std::vector<boost::any> arglist)
{
	Result = (double) rand();
}

boost::any Random::GetResult()
{
	return Result;
}

Random::~Random()
{
}

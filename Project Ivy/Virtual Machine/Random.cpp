#include "Random.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("random", Random, 2);

void Random::Execute(std::vector<boost::any> arglist)
{

}

boost::any Random::GetResult()
{
	return Result;
}

Random::~Random()
{
}

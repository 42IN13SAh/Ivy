#include "Random.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("random", Random);

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

#include "DateTime.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("dateTime", DateTime, 0);

void DateTime::Execute(std::vector<boost::any> arglist)
{

}

boost::any DateTime::GetResult()
{
	return Result;
}

DateTime::~DateTime()
{
}

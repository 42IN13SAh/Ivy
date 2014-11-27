#include "ReadFileLines.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("readFileLines", ReadFileLines);

void ReadFileLines::Execute(std::vector<boost::any> arglist)
{

}

boost::any ReadFileLines::GetResult()
{
	return Result;
}

ReadFileLines::~ReadFileLines()
{
}

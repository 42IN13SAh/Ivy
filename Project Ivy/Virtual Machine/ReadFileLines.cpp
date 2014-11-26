#include "ReadFileLines.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("readFileLines", ReadFileLines, 1);

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

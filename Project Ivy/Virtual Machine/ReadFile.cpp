#include "ReadFile.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("readFile", ReadFile, 1);

void ReadFile::Execute(std::vector<boost::any> arglist)
{

}

boost::any ReadFile::GetResult()
{
	return Result;
}

ReadFile::~ReadFile()
{
}

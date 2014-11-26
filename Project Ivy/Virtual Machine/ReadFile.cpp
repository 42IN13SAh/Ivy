#include "ReadFile.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("readFile", ReadFile);

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

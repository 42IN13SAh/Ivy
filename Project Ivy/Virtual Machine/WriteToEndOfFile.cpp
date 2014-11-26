#include "WriteToEndOfFile.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("writeToEndOfFile", WriteToEndOfFile);

void WriteToEndOfFile::Execute(std::vector<boost::any> arglist)
{

}

boost::any WriteToEndOfFile::GetResult()
{
	return Result;
}

WriteToEndOfFile::~WriteToEndOfFile()
{
}

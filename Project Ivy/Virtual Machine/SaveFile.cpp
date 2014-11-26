#include "SaveFile.h"
#include "InternalFunctionFactory.h"

REGISTER_CLASS("saveFile", SaveFile, 2);

void SaveFile::Execute(std::vector<boost::any> arglist)
{

}

boost::any SaveFile::GetResult()
{
	return Result;
}

SaveFile::~SaveFile()
{
}

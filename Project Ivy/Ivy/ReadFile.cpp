#include "ReadFile.h"

void ReadFile::Execute(std::vector<boost::any> arglist)
{
	//"D:\\local\\test.txt"
	std::string filepath = boost::any_cast<std::string>(arglist[0]);
	std::ifstream file(filepath, std::ios::in | std::ios::binary);
	Result = (std::string((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>()));
}

boost::any ReadFile::GetResult()
{
	return Result;
}

ReadFile::~ReadFile()
{
}

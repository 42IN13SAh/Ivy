#include "ReadFile.h"

void ReadFile::Execute(std::vector<boost::any> arglist)
{
	//D:\\local\\test.txt"
	std::string filepath = boost::any_cast<std::string>(arglist[0]);
	std::ifstream file;
	file.open(filepath);
	std::stringstream line;

	char c = file.get();
	while (!file.eof()) 
	{
		line << c;
		c = file.get();
	}
	Result = line.str();
}

boost::any ReadFile::GetResult()
{
	return Result;
}

ReadFile::~ReadFile()
{
}

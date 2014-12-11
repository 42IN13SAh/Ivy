#include "ReadFile.h"
#include <fstream>
#include <iostream>
#include <string>

void ReadFile::Execute(std::vector<boost::any> arglist)
{
	//D:\\local\\test.txt"
	std::string filepath = boost::any_cast<std::string>(arglist[0]);
	std::ifstream file;
	file.open(filepath);
	std::string tempstring;
	std::string resultstring;
	while (std::getline(file, tempstring))
	{
		resultstring += tempstring + " ";
	}
	Result = resultstring;
}

boost::any ReadFile::GetResult()
{
	return Result;
}

ReadFile::~ReadFile()
{
}

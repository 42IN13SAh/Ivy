// TestApplication.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Tokenizer.h"
#include <fstream>


int _tmain(int argc, _TCHAR* argv[])
{
	Tokenizer tok;
	std::string line;
	std::vector<std::string> lines;
	std::ifstream file;
	file.open("test code 1.0.txt");
	while (std::getline(file, line)){
		lines.push_back(line);
	}
	file.close();
	tok.tokenize(&lines[0], lines.size());


	return 0;
}


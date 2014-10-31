#pragma once
#include <string>

class VarCompilerToken
{
public:
	VarCompilerToken(std::string);
	~VarCompilerToken();
private:
	std::string name;
};


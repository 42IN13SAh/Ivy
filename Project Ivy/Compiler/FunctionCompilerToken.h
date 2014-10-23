#pragma once
#include <string>
#include <vector>

#include "CompilerToken.h"

using namespace std;

class FunctionCompilerToken :
	public CompilerToken
{
public:
	FunctionCompilerToken();
	~FunctionCompilerToken();

private:
	//vector<boost::any> data;
	string functionName;
};


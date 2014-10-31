#pragma once
#include <string>

#include "CompilerToken.h"

using namespace std;

class FunctionCompilerToken :
	public CompilerToken
{
public:
	FunctionCompilerToken();
	~FunctionCompilerToken();

private:
	string functionName;
};


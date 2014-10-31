#pragma once
#include <string>
#include <vector>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

using namespace std;

class FunctionCompilerToken :
	public CompilerToken
{
public:
	FunctionCompilerToken();
	~FunctionCompilerToken();

private:
	string name;
	vector<ReturnValueCompilerToken*> arguments;
	ReturnValueCompilerToken* returnValue;
};


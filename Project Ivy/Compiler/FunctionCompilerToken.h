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
	FunctionCompilerToken(std::string);
	virtual ~FunctionCompilerToken();

	void setName(string);
	void addArgument(ReturnValueCompilerToken*);
	void addArgumentName(string);
	
	string getName();
	vector<ReturnValueCompilerToken*> getArguments();
	vector<string> getArgumentNames();

private:
	string name;
	vector<ReturnValueCompilerToken*> arguments;
	vector<string> argumentNames;
};
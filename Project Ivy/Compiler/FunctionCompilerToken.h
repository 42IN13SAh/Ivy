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
	void setResult(boost::any);
	
	string getName();
	vector<ReturnValueCompilerToken*> getArguments();
	vector<string> getArgumentNames();
	boost::any getResult();

private:
	string name;
	vector<ReturnValueCompilerToken*> arguments;
	vector<string> argumentNames;
	boost::any result;
};
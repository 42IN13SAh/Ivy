#pragma once
#include <string>
#include <vector>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class FunctionCompilerToken :
	public CompilerToken
{
public:
	FunctionCompilerToken(std::string);
	virtual ~FunctionCompilerToken();
	void setName(std::string);
	void addArgument(ReturnValueCompilerToken*);
	void addArgumentName(std::string);
	void setResult(boost::any);
	std::string getName();
	std::vector<ReturnValueCompilerToken*>& getArguments();
	std::vector<std::string> getArgumentNames();
	boost::any getResult();
private:
	std::string name;
	std::vector<ReturnValueCompilerToken*> arguments;
	std::vector<std::string> argumentNames;
	boost::any result;
};
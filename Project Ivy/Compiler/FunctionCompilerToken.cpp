#include "FunctionCompilerToken.h"


FunctionCompilerToken::FunctionCompilerToken(std::string name)
{
	this->name = name;
}


FunctionCompilerToken::~FunctionCompilerToken()
{
	for each(ReturnValueCompilerToken* rv in arguments) {
		//delete rv;
	}
}


void FunctionCompilerToken::setName(string name) {
	this->name = name;
}

void FunctionCompilerToken::addArgument(ReturnValueCompilerToken* rvct) {
	arguments.push_back(rvct);
}

void FunctionCompilerToken::addArgumentName(string name) {
	argumentNames.push_back(name);
}

string FunctionCompilerToken::getName() {
	return name;
}

vector<ReturnValueCompilerToken*> FunctionCompilerToken::getArguments() {
	return arguments;
}

vector<string> FunctionCompilerToken::getArgumentNames() {
	return argumentNames;
}

void FunctionCompilerToken::setResult(boost::any result) {
	this->result = result;
}

boost::any FunctionCompilerToken::getResult() {
	return this->result;
}
#include "FunctionCompilerToken.h"


FunctionCompilerToken::FunctionCompilerToken(std::string name)
{
	this->name = name;
}


FunctionCompilerToken::~FunctionCompilerToken()
{
	for each(ReturnValueCompilerToken* rv in arguments) {
		delete rv;
	}
}

void FunctionCompilerToken::setName(std::string name) {
	this->name = name;
}

void FunctionCompilerToken::addArgument(ReturnValueCompilerToken* rvct) {
	arguments.push_back(rvct);
}

void FunctionCompilerToken::addArgumentName(std::string name) {
	argumentNames.push_back(name);
}

std::string FunctionCompilerToken::getName() {
	return name;
}

std::vector<ReturnValueCompilerToken*>& FunctionCompilerToken::getArguments() {
	return arguments;
}

std::vector<std::string> FunctionCompilerToken::getArgumentNames() {
	return argumentNames;
}

void FunctionCompilerToken::setResult(boost::any result) {
	this->result = result;
}

boost::any FunctionCompilerToken::getResult() {
	return this->result;
}
#include <iostream>
#include "AssignCompilerToken.h"

AssignCompilerToken::AssignCompilerToken(std::string name, ReturnValueCompilerToken* value, TokenType assignOp)
{
	this->name = name;
	this->value = value;
	this->assignOp = assignOp;
}

AssignCompilerToken::~AssignCompilerToken()
{
	delete value;
}

std::string AssignCompilerToken::getName() {
	return name;
}

ReturnValueCompilerToken* AssignCompilerToken::getReturnValue() {
	return value;
}

TokenType AssignCompilerToken::getAssignOp()
{
	return assignOp;
}
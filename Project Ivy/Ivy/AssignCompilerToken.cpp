#include <iostream>
#include "AssignCompilerToken.h"

AssignCompilerToken::AssignCompilerToken(std::string name, boost::shared_ptr<ReturnValueCompilerToken> value, TokenType::TokenType assignOp)
{
	this->name = name;
	this->value = value;
	this->assignOp = assignOp;
}

AssignCompilerToken::~AssignCompilerToken()
{
	
}

std::string AssignCompilerToken::getName() {
	return name;
}

boost::shared_ptr<ReturnValueCompilerToken> AssignCompilerToken::getReturnValue() {
	return value;
}

TokenType::TokenType AssignCompilerToken::getAssignOp()
{
	return assignOp;
}
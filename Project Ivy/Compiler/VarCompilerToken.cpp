#include "VarCompilerToken.h"

VarCompilerToken::VarCompilerToken(std::string name)
{
	this->name = name;
	this->frontOperator = TokenType::Null;
	this->backOperator = TokenType::Null;
}

VarCompilerToken::~VarCompilerToken()
{
}

void VarCompilerToken::setBackOperator(TokenType o) {
	this->backOperator = o;
}

void VarCompilerToken::setFrontOperator(TokenType o) {
	this->frontOperator = o;
}

std::string VarCompilerToken::getName()
{
	return name;
}

TokenType VarCompilerToken::getBackOperator()
{
	return this->backOperator;
}

TokenType VarCompilerToken::getFrontOperator()
{
	return this->frontOperator;
}

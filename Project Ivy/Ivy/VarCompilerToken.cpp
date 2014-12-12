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

void VarCompilerToken::setBackOperator(TokenType::TokenType o) 
{
	this->backOperator = o;
}

void VarCompilerToken::setFrontOperator(TokenType::TokenType o) 
{
	this->frontOperator = o;
}

std::string VarCompilerToken::getName()
{
	return name;
}

TokenType::TokenType VarCompilerToken::getBackOperator()
{
	return this->backOperator;
}

TokenType::TokenType VarCompilerToken::getFrontOperator()
{
	return this->frontOperator;
}

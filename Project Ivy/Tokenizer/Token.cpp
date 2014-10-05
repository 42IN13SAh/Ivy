#include "Token.h"

Token::Token(int lineNumber, int linePosition, int level, std::string description, TokenType tokenType, Token* partner)
{
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
	this->level = level;
	this->description = description;
	this->tokenType = tokenType;
	this->partner = partner;
}

int Token::getLineNumber()
{
	return lineNumber;
}

int Token::getLinePosition()
{
	return linePosition;
}

int Token::getLevel()
{
	return level;
}

std::string Token::getDescription()
{
	return description;
}

TokenType Token::getTokenType()
{
	return tokenType;
}

Token* Token::getPartner()
{
	return partner;
}

Token::~Token()
{
	delete[] partner;
}

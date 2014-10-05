#include "Token.h"

// Constructors
Token::Token()
{

}

Token::Token(int lineNumber, int linePosition, int level, std::string description, TokenType tokenType, Token* partner)
{
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
	this->level = level;
	this->description = description;
	this->tokenType = tokenType;
	this->partner = partner;
}

// Destructor
// Check dem memory leaks!!!
Token::~Token()
{
	delete partner;
}

// Public methods
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

void Token::setLineNumber(int lineNumber)
{
	this->lineNumber = lineNumber;
}

void Token::setLinePosition(int linePosition)
{
	this->linePosition = linePosition;
}

void Token::setLevel(int level)
{
	this->level = level;
}

void Token::setDescription(std::string description)
{
	this->description = description;
}

void Token::setTokenType(TokenType tokenType)
{
	this->tokenType = tokenType;
}

void Token::setPartner(Token *partner)
{
	this->partner = partner;
}

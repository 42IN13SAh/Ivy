#include "Token.h"

Token::Token(int syntaxID, int lineNumber, int linePosition, int level, std::string description, TokenType::TokenType tokenType, ParentType parentType, Token* partner)
{
	this->syntaxID = syntaxID;
	this->lineNumber = lineNumber;
	this->linePosition = linePosition;
	this->level = level;
	this->description = description;
	this->tokenType = tokenType;
	this->parentType = parentType;
	this->partner = partner;
}

// Destructor
Token::~Token()
{

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

TokenType::TokenType Token::getTokenType()
{
	return tokenType;
}

ParentType Token::getParentType() {
	return parentType;
}

Token* Token::getPartner()
{
	return partner;
}

int Token::getSyntaxID(){
	return syntaxID;
}

void Token::setPartner(Token *partner)
{
	this->partner = partner;
}
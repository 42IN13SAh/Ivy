#pragma once
#include <string>
#include "TokenType.h"

class Token
{
public:

	Token(int lineNumber, int linePosition, int level, std::string description, TokenType tokenType, Token* partner);
	virtual ~Token();

	int getLineNumber();
	int getLinePosition();
	int getLevel();
	std::string getDescription();
	TokenType getTokenType();
	Token* getPartner();

private:
	int lineNumber;
	int linePosition;
	int level;
	std::string description;
	TokenType tokenType;
	Token* partner;	
};


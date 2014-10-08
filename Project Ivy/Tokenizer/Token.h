#pragma once
#include <string>
#include "TokenType.h"

class Token
{
public:

	Token();
	Token(int lineNumber, int linePosition, int level, std::string description, TokenType tokenType, Token* partner);
	virtual ~Token();

	int getLineNumber();
	int getLinePosition();
	int getLevel();
	std::string getDescription();
	TokenType getTokenType();
	Token* getPartner();

	void setLineNumber(int lineNumber);
	void setLinePosition(int linePosition);
	void setLevel(int level);
	void setDescription(std::string description);
	void setTokenType(TokenType tokenType);
	void setPartner(Token *partner);

private:
	int lineNumber;
	int linePosition;
	int level;
	std::string description;
	TokenType tokenType;
	Token* partner;	
};


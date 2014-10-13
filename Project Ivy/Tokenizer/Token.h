#pragma once
#include <string>
#include "TokenType.h"

class Token
{
public:

	Token();
	Token(int syntaxID, int lineNumber, int linePosition, int level, std::string description, TokenType tokenType, Token* partner);
	virtual ~Token();
	int getLineNumber();
	int getLinePosition();
	int getLevel();
	std::string getDescription();
	TokenType getTokenType();
	Token* getPartner();
	int getSyntaxID();
	void setPartner(Token *partner);

private:
	int syntaxID;
	int lineNumber;
	int linePosition;
	int level;
	std::string description;
	TokenType tokenType;
	Token* partner;	
};


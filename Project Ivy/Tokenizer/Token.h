#pragma once
#include <string>
#include "TokenType.h"
#include "ParentTokenType.h"

class Token
{
public:
	Token(int syntaxID, int lineNumber, int linePosition, int level, std::string description, TokenType tokenType, ParentType parentType, Token* partner);
	virtual ~Token();
	int getLineNumber();
	int getLinePosition();
	int getLevel();
	std::string getDescription();
	TokenType getTokenType();
	ParentType getParentType();
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
	ParentType parentType;
	Token* partner;	
};


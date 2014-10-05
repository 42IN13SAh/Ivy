#pragma once
#include <string>
#include <vector>
#include "TokenType.h"

class Syntax
{
public:
	Syntax(int id, std::string regexPattern, TokenType tokenType);
	virtual ~Syntax();

	void setShouldPush(bool shouldPush);
	int getID();
	std::string getRegexPattern();
	std::vector<Syntax> getPartners();
	std::vector<Syntax> getPossibleFollowUps();
	TokenType getTokenType();
	bool getShouldPush();

private:
	int id;
	std::string regexPattern;
	std::vector<Syntax> partners;
	std::vector<Syntax> possibleFollowUps;
	TokenType tokenType;
	bool shouldPush;
};


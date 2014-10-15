#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "TokenType.h"
class Syntax
{
public:
	Syntax(int id, std::string regexPattern, TokenType tokenType, std::vector<int> partnerIds,
		std::vector<int> possibleFollowUpIds, bool shouldPush);
	virtual ~Syntax();
	int getID();
	std::string getRegexPattern();
	std::vector<Syntax*> getPartners(std::unordered_map<int, Syntax*> syntaxMap);
	std::vector<Syntax*> getPossibleFollowUps(std::unordered_map<int, Syntax*> syntaxMap);
	TokenType getTokenType();
	bool getShouldPush();

private:
	int id;
	std::string regexPattern;
	std::vector<Syntax*> partners;
	std::vector<Syntax*> possibleFollowUps;
	std::vector<int> partnerIds;
	std::vector<int> possibleFollowUpIds;
	TokenType tokenType;
	bool shouldPush;
};


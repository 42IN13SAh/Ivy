#pragma once
#include <string>
#include <vector>
#include <boost\regex.hpp>
#include "TokenType.h"
#include "ParentTokenType.h"
class Syntax
{
public:
	Syntax(int id, boost::regex regexPattern, TokenType::TokenType tokenType, ParentType parentType, std::vector<int> partnerIds,
		std::vector<int> possibleFollowUpIds, bool shouldPush);
	virtual ~Syntax();
	int getID();
	const boost::regex getRegexPattern();
	const std::vector<Syntax*> getPartners();
	const std::vector<Syntax*> getPossibleFollowUps();
	TokenType::TokenType getTokenType();
	ParentType getParentType();
	bool getShouldPush();
	void initPartners(std::map<int, Syntax*>& syntaxMap);
	void initFollowUps(std::map<int, Syntax*>& syntaxMap);

private:
	int id;
	boost::regex regexPattern;
	std::vector<Syntax*> partners;
	std::vector<Syntax*> possibleFollowUps;
	std::vector<int> partnerIds;
	std::vector<int> possibleFollowUpIds;
	TokenType::TokenType tokenType;
	ParentType parentType;
	bool shouldPush;
};
#pragma once
#include <string>
#include <vector>
#include <boost\regex.hpp>
#include "TokenType.h"
class Syntax
{
public:
	Syntax(int id, boost::regex regexPattern, TokenType tokenType, std::vector<int> partnerIds,
		std::vector<int> possibleFollowUpIds, bool shouldPush);
	virtual ~Syntax();
	int getID();
	const boost::regex getRegexPattern();
	const std::vector<Syntax*> getPartners();
	const std::vector<Syntax*> getPossibleFollowUps();
	TokenType getTokenType();
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
	TokenType tokenType;
	bool shouldPush;
};














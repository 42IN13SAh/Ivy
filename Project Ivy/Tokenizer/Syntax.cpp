#include "Syntax.h"

Syntax::Syntax(int id, boost::regex regexPattern, TokenType tokenType, std::vector<int> partnerIds,
	std::vector<int> possibleFollowUpIds, bool shouldPush)
{
	this->id = id;
	this->regexPattern = regexPattern;
	this->tokenType = tokenType;
	this->partnerIds = partnerIds;
	this->possibleFollowUpIds = possibleFollowUpIds;
	this->shouldPush = shouldPush;

}

Syntax::~Syntax()
{
}

int Syntax::getID()
{
	return id;
}

const boost::regex Syntax::getRegexPattern()
{
	return regexPattern;
}

const std::vector<Syntax*> Syntax::getPartners()
{
	return partners;
}

const std::vector<Syntax*> Syntax::getPossibleFollowUps()
{
	return possibleFollowUps;
}

TokenType Syntax::getTokenType()
{
	return tokenType;
}

bool Syntax::getShouldPush()
{
	return shouldPush;
}

void Syntax::initFollowUps(std::map<int, Syntax*>& syntaxMap)
{
	for (int i = 0; i < possibleFollowUpIds.size(); i++)
	{
		possibleFollowUps.push_back(syntaxMap[possibleFollowUpIds[i]]);
	}
}

void Syntax::initPartners(std::map<int, Syntax*>& syntaxMap)
{
	for (int i = 0; i < partnerIds.size(); i++){
		partners.push_back(syntaxMap[partnerIds[i]]);
	}
}
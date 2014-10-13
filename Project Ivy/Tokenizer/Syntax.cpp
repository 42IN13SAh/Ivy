#include "Syntax.h"

Syntax::Syntax()
{

}

Syntax::Syntax(int id, std::string regexPattern, TokenType tokenType, std::vector<int> partnerIds,
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

std::string Syntax::getRegexPattern()
{
	return regexPattern;
}

std::vector<Syntax*> Syntax::getPartners(std::unordered_map<int, Syntax*> syntaxMap)
{
	if (partners.size() == 0){
		for (int i = 0; i < partnerIds.size(); i++){
			partners.push_back(syntaxMap[partnerIds[i]]);
		}
	}
	return partners;
}

std::vector<Syntax*> Syntax::getPossibleFollowUps(std::unordered_map<int, Syntax*> syntaxMap)
{
	if (possibleFollowUps.size() == 0){
		for (int i = 0; i < possibleFollowUpIds.size(); i++)
		{
			possibleFollowUps.push_back(syntaxMap[possibleFollowUpIds[i]]);
		}
	}
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


#include "Syntax.h"

Syntax::Syntax(int id, std::string regexPattern, TokenType tokenType)
{
	this->id = id;
	this->regexPattern = regexPattern;
	this->tokenType = tokenType;
	this->shouldPush = false;
}

void Syntax::setShouldPush(bool shouldPush)
{
	this->shouldPush = shouldPush;
}

int Syntax::getID()
{
	return id;
}

std::string Syntax::getRegexPattern()
{
	return regexPattern;
}

std::vector<Syntax> Syntax::getPartners()
{
	return partners;
}

std::vector<Syntax> Syntax::getPossibleFollowUps()
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



Syntax::~Syntax()
{
}

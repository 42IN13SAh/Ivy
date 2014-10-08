#include "SyntaxManager.h"
#include <iostream>

SyntaxManager::SyntaxManager()
{
	syntaxMap = new std::map<int, Syntax>();
	fullSyntaxVector = new std::vector<Syntax>();
}

SyntaxManager::~SyntaxManager()
{
	delete syntaxMap;
	delete fullSyntaxVector;
}

void SyntaxManager::jsonToSyntaxMap()
{
	// Load file.

	// Code...

	fillFullSyntaxVector();
}

void SyntaxManager::fillFullSyntaxVector()
{
	for (auto &iter : *syntaxMap)
	{
		fullSyntaxVector->push_back(iter.second);
	}
}

std::vector<Syntax> SyntaxManager::getFollowupVector(int syntaxId)
{
	if (syntaxId != -1)
	{
		std::vector<Syntax> collection = syntaxMap->find(syntaxId)->second.getPossibleFollowUps();

		if (collection.size() != 0)
			return collection;
	}
	
	return *fullSyntaxVector;
}
#include "SyntaxManager.h"
#include <iostream>

SyntaxManager::SyntaxManager()
{
	syntaxMap = new std::map<int, Syntax>();
}

SyntaxManager::~SyntaxManager()
{
	delete syntaxMap;
}

void SyntaxManager::jsonToSyntaxMap()
{

}
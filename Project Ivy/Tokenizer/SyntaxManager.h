#pragma once
#include <vector>
#include "Jzon.h"
#include "Syntax.h"
#include "TokenType.h"

class SyntaxManager
{
public:
	SyntaxManager();
	virtual ~SyntaxManager();
	void jsonToSyntaxMap();
	void fillSyntaxList();
	std::vector<Syntax*> getFollowupVector(int& syntaxId);
	std::map<int, Syntax*>* getSyntaxMap();
	bool hasKeyWord(std::string keyWord);
private:
	std::vector<std::string> reservedKeyWords;
	std::map<int, Syntax*> syntaxMap;
	std::vector<Syntax*> syntaxList;
	std::map<std::string, TokenType> tokenDictionary;
	std::map<std::string, ParentType> parentDictionary;
	void initTokenDictionary();
	void initParentDictionary();
};


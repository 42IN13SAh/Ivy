#pragma once
#include <unordered_map>
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
	std::vector<Syntax*> getFollowupVector(int syntaxId);
	std::unordered_map<int, Syntax*> getSyntaxMap();
	bool hasKeyWord(std::string keyWord);
private:
	std::vector<std::string> reservedKeyWords;
	std::unordered_map<int, Syntax*> syntaxMap;
	std::vector<Syntax*> syntaxList;
	std::unordered_map<std::string, TokenType> tokenDictionary;
	void initTokenDictionary();
};


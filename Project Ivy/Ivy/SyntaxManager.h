#pragma once
#include <vector>
#include <map>
#include "Jzon.h"
#include "Syntax.h"
#include "TokenType.h"
#include "ParentTokenType.h"

class SyntaxManager
{
public:
	SyntaxManager();
	virtual ~SyntaxManager();
	void jsonToSyntaxMap();
	void fillSyntaxList();
	std::vector<Syntax*> getFollowupVector(int& syntaxId);
	std::map<int, Syntax*>* getSyntaxMap();
	Syntax* getSyntax(int id);
	bool hasKeyWord(std::string keyWord);

	static SyntaxManager* Instance() { static SyntaxManager instance; return &instance; }
private:
	std::vector<std::string> reservedKeyWords;
	std::map<int, Syntax*> syntaxMap;
	std::vector<Syntax*> syntaxList;
	std::map<std::string, TokenType::TokenType> tokenDictionary;
	std::map<std::string, ParentType> parentDictionary;
	void initTokenDictionary();
	void initParentDictionary();
};
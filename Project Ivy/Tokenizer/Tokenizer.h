#pragma once
#include <stack>
#include <string>
#include <list>
#include "Token.h"
#include "SyntaxManager.h"

class Tokenizer
{
public:
	Tokenizer(void);
	virtual ~Tokenizer(void);
	void tokenize(std::string* input, int size);
	void tokenize(const char* input);
	std::list<Token*> getTokenList();
private:
	const char* trim(const char* str, int& lineposition);
	std::stack<Token*> partnerStack;
	std::list<Token*> tokenList;
	SyntaxManager syntaxManager;
	bool validateKeyWordIfGoodAddToList(Token* token);
	void tokenPartnerCheck(Syntax* syntax, Token* token, int& level);
};

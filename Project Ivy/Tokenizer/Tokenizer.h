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

	void tokenize(std::string *input, int size);

private:
	std::stack<Token> *partnerStack;
	std::list<Token> *tokenList;
	SyntaxManager *syntaxManager;
};

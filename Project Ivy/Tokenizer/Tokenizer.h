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
	std::list<Token> getTokenList();

	static inline std::string &ltrim(std::string &s);
	static inline std::string &rtrim(std::string &s);
	static inline std::string &trim(std::string &s);

private:
	std::stack<Token> *partnerStack;
	std::list<Token> *tokenList;
	SyntaxManager *syntaxManager;
};

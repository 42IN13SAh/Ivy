#pragma once
#include <stack>
#include "Token.h"
#include <string>

class Tokenizer
{
public:
	Tokenizer(void);
	virtual ~Tokenizer(void);

	void tokenize(std::string input);
private:
	std::stack<Token> partnerStack;
};

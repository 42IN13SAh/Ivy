#pragma once
#include <stack>
#include <string>
#include <list>
#include "Token.h"
#include "SyntaxManager.h"
#include "BadSyntaxException.h"

class Tokenizer
{
public:
	Tokenizer(void);
	virtual ~Tokenizer(void);
	void tokenize(std::string* input, int size);
	void tokenize(const char* input);
	std::list<Token*> getTokenList();
	const std::vector<BadSyntaxException>& getErrorList();
private:
	const char* trim(const char* str, int& lineposition);
	std::stack<Token*> partnerStack;
	std::list<Token*> tokenList;
	std::vector<BadSyntaxException> errorList;
	SyntaxManager syntaxManager;
	//bool validateKeyWordIfGoodAddToList(Token* token);
	bool tokenPartnerCheck(Syntax* syntax, Token* token, int& level, int& linenumber, int& lineposition);
};
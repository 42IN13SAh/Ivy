#pragma once
#include <stack>
#include <string>
#include <list>
#include "Token.h"
#include "SyntaxManager.h"
#include "BaseException.h"

class Tokenizer
{
public:
	Tokenizer(void);
	virtual ~Tokenizer(void);
	void tokenize(std::string* input, int size);
	void tokenize(const char* input);
	std::list<Token*> getTokenList();
	const std::vector<BaseException>& getErrorList();
private:
	const char* trim(const char* str, int& lineposition);
	std::stack<Token*> partnerStack;
	std::list<Token*> tokenList;
	std::vector<BaseException> errorList;
	SyntaxManager syntaxManager;
	//bool validateKeyWordIfGoodAddToList(Token* token);
	bool tokenPartnerCheck(Syntax* syntax, Token* token, int& level, int& linenumber, int& lineposition);
	const std::vector<std::string> getSyntaxValuesAsString(std::vector<Syntax*>);
};
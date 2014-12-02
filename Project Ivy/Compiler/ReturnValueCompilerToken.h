#pragma once
#include <queue>
#include <stack>
#include "CompilerToken.h"
#include "boost/any.hpp"
#include "../Tokenizer/TokenType.h"

class ReturnValueCompilerToken : public CompilerToken
{
public:
	ReturnValueCompilerToken();
	virtual ~ReturnValueCompilerToken();
	bool isEmpty();
	void addValueToVector(boost::any);
	void pushOperatorToStack(TokenType);
	TokenType peekOperatorStack();
	void popOperatorStack();
	bool hasOpenParenthisOnStack();
	void completeRPNVector();
	std::queue<boost::any>& getRPN();
private:
	std::queue<boost::any> rpnVector;
	std::stack<TokenType> operatorStack;
	int openParenthisCounter;
};


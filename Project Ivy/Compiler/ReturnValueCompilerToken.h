#pragma once
#include <stack>
//#include <vector>
#include "CompilerToken.h"
#include "boost/any.hpp"
#include "../Tokenizer/TokenType.h"

class ReturnValueCompilerToken : public CompilerToken
{
public:
	ReturnValueCompilerToken();
	virtual ~ReturnValueCompilerToken();

	void addValueToVector(boost::any);
	void pushOperatorToStack(TokenType);
	TokenType peekOperatorStack();
	void popOperatorStack();

	void completeRPNVector();
	std::stack<boost::any>& getRPN();

	virtual ReturnValueCompilerToken* Get() { return this; }

private:
	std::stack<boost::any> rpnVector;
	std::stack<TokenType> operatorStack;
};


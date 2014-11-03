#pragma once
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"
#include "../Tokenizer/TokenType.h"

class SubConditionCompilerToken : public CompilerToken
{
public:
	SubConditionCompilerToken();
	virtual ~SubConditionCompilerToken();

	//enum SubConditionOperator { GreaterThen, SmallerThen, SmallerEquals, GreaterEquals, Is, Not };

	void setLeft(ReturnValueCompilerToken*);
	void setRight(ReturnValueCompilerToken*);
	void setOperator(TokenType);

private:
	TokenType scOperator;
	ReturnValueCompilerToken* left;
	ReturnValueCompilerToken* right;
};


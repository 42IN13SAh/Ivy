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

	virtual SubConditionCompilerToken* Get() { return this; }

private:
	TokenType scOperator;
	ReturnValueCompilerToken* left;
	ReturnValueCompilerToken* right;
};


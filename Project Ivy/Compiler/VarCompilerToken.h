#pragma once
#include <string>
#include "../Tokenizer/TokenType.h"

class VarCompilerToken
{
public:
	VarCompilerToken(std::string);
	virtual ~VarCompilerToken();

	void setFrontOperator(TokenType);
	void setBackOperator(TokenType);
	std::string getName();
	TokenType getFrontOperator();
	TokenType getBackOperator();

	//virtual VarCompilerToken* Get() { return this; }

private:
	std::string name;

	TokenType frontOperator;
	TokenType backOperator;
};


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

private:
	std::string name;

	TokenType frontOperator;
	TokenType backOperator;
};


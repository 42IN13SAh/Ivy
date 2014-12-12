#pragma once
#include <string>
#include "TokenType.h"
#include "CompilerToken.h"
class VarCompilerToken : public CompilerToken
{
public:
	VarCompilerToken(std::string);
	virtual ~VarCompilerToken();

	void setFrontOperator(TokenType::TokenType);
	void setBackOperator(TokenType::TokenType);
	std::string getName();
	TokenType::TokenType getFrontOperator();
	TokenType::TokenType getBackOperator();
private:
	std::string name;

	TokenType::TokenType frontOperator;
	TokenType::TokenType backOperator;
};


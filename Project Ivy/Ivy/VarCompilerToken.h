#pragma once
#include <string>
#include "TokenType.h"
#include "CompilerToken.h"
class VarCompilerToken : public CompilerToken
{
public:
	VarCompilerToken(std::string);
	virtual ~VarCompilerToken();

	void setFrontOperator(TokenType);
	void setBackOperator(TokenType);
	std::string getName();
	TokenType getFrontOperator();
	TokenType getBackOperator();
private:
	std::string name;

	TokenType frontOperator;
	TokenType backOperator;
};


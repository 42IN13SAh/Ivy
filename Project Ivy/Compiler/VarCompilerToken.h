#pragma once
#include <string>
#include "../Tokenizer/TokenType.h"
#include <boost\any.hpp>

class VarCompilerToken
{
public:
	VarCompilerToken(std::string);
	virtual ~VarCompilerToken();

	void setFrontOperator(TokenType);
	void setBackOperator(TokenType);
	void setResult(boost::any);
	std::string getName();
	boost::any getResult();
	TokenType getFrontOperator();
	TokenType getBackOperator();

private:
	std::string name;
	boost::any result;

	TokenType frontOperator;
	TokenType backOperator;
};


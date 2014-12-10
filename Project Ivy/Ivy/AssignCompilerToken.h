#pragma once
#include <string>
#include "TokenType.h"
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class AssignCompilerToken :
	public CompilerToken
{
public:
	AssignCompilerToken(std::string, ReturnValueCompilerToken*, TokenType tokenType);
	virtual ~AssignCompilerToken();
	std::string getName();
	ReturnValueCompilerToken* getReturnValue();
	TokenType getAssignOp();
private:
	std::string name;
	ReturnValueCompilerToken* value;
	TokenType assignOp;
};
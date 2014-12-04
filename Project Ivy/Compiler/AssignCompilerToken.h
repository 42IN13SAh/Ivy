#pragma once
#include <string>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class AssignCompilerToken :
	public CompilerToken
{
public:
	AssignCompilerToken(std::string, ReturnValueCompilerToken*, TokenType);
	virtual ~AssignCompilerToken();
	std::string getName();
	ReturnValueCompilerToken* getReturnValue();
	TokenType getAssignOp() { return assignOp; }
private:
	std::string name;
	ReturnValueCompilerToken* value;
	TokenType assignOp;
};


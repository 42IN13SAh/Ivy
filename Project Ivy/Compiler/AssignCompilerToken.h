#pragma once
#include <string>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class AssignCompilerToken :
	public CompilerToken
{
public:
	AssignCompilerToken(std::string, ReturnValueCompilerToken*);
	virtual ~AssignCompilerToken();

	std::string getName();
	ReturnValueCompilerToken* getReturnValue();

	virtual AssignCompilerToken* Get() { return this; }

private:
	std::string name;
	ReturnValueCompilerToken* value;
};


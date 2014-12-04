#pragma once
#include <vector>
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class ConditionCompilerToken : public CompilerToken
{
public:
	ConditionCompilerToken(ReturnValueCompilerToken*);
	virtual ~ConditionCompilerToken();
	ReturnValueCompilerToken* getReturnValueCompilerToken() { return rvct; }

private:
	ReturnValueCompilerToken* rvct;
};


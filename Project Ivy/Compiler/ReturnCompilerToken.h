#pragma once
#include "CompilerToken.h"
#include "ReturnValueCompilerToken.h"

class ReturnCompilerToken :
	public CompilerToken
{
public:
	ReturnCompilerToken(ReturnValueCompilerToken*);
	virtual ~ReturnCompilerToken();

	ReturnValueCompilerToken* getReturnValueCompilerToken() { return rvct; }

	//virtual ReturnCompilerToken* Get() { return this; }
private:
	ReturnValueCompilerToken* rvct;
};


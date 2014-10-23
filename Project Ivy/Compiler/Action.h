#pragma once

#include "AddCompilerToken.h"

class Action
{
public:
	Action();
	~Action();

private:
	Action *nextAction;
	Action *onFalseAction;
	CompilerToken compilerToken;
};


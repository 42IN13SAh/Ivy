#pragma once

#include "CompilerToken.h"

class Action
{
public:
	Action();
	~Action();

	Action *getNextAction();

private:
	Action *nextAction;
	Action *onFalseAction;
	CompilerToken compilerToken;
};


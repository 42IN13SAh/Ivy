#pragma once

#include "CompilerToken.h"

class VirtualMachine;

class Action
{
public:
	Action();
	~Action();

	virtual Action *getNextAction(VirtualMachine *vm);

protected:
	Action *nextAction;
	Action *onFalseAction;
	CompilerToken compilerToken;
};


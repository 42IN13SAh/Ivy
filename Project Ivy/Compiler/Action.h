#pragma once

#include "CompilerToken.h"

class VirtualMachine;

class Action
{
public:
	Action();
	~Action();

	void setNextAction(Action*);
	void setFalseAction(Action*);
	Action* getNextAction();

protected:
	Action* nextAction;
	Action* onFalseAction;
	CompilerToken compilerToken;
};


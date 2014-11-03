#pragma once

#include "Action.h"

class DoNothingAction
	: public Action
{
public:
	DoNothingAction();
	virtual ~DoNothingAction();
	//Action* getNextAction(VirtualMachine* vm);
};


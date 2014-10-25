#pragma once

#include "Action.h"

class DoNothingAction
	: public Action
{
public:
	DoNothingAction();
	~DoNothingAction();
	Action *getNextAction(VirtualMachine *vm);
};


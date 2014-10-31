#include "Action.h"
#include "VirtualMachine.h"

Action::Action()
{
}


Action::~Action()
{
}

Action* Action::getNextAction(VirtualMachine *vm)
{
	if (compilerToken.execute(vm))
	{
		return nextAction;
	}
	else
	{
		return onFalseAction;
	}
}
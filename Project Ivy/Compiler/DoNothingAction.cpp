#include "DoNothingAction.h"
#include "../Virtual Machine/VirtualMachine.h"

DoNothingAction::DoNothingAction()
{
}


DoNothingAction::~DoNothingAction()
{
}

Action* DoNothingAction::getNextAction(VirtualMachine *vm)
{
	return nextAction;
}
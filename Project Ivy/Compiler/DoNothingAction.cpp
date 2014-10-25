#include "DoNothingAction.h"
#include "VirtualMachine.h"

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
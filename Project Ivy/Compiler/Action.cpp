#include "Action.h"
#include "../Virtual Machine/VirtualMachine.h"

Action::Action()
{
}

void Action::setNextAction(Action* a) { nextAction = a; }
void Action::setFalseAction(Action* a) { onFalseAction = a; }
Action* Action::getNextAction() { return nextAction; }

Action::~Action()
{
}
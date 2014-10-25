#include "DoNothingAction.h"


DoNothingAction::DoNothingAction()
{
}


DoNothingAction::~DoNothingAction()
{
}

Action* Action::getNextAction()
{
	return nextAction;
}
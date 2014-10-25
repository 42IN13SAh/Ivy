#include "Action.h"


Action::Action()
{
}


Action::~Action()
{
}

Action* Action::getNextAction()
{
	if (compilerToken.execute())
	{
		return nextAction;
	}
	else
	{
		return onFalseAction;
	}
}
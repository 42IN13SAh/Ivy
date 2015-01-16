#include "Action.h"
Action::Action()
{
}

void Action::setNextAction(Action* a) 
{ 
	nextAction = a; 
}

void Action::setFalseAction(Action* a) 
{ 
	onFalseAction = a; 
}

Action* Action::getNextAction() 
{ 
	return nextAction; 
}

Action* Action::getFalseAction() 
{ 
	return onFalseAction; 
}

boost::shared_ptr<CompilerToken> Action::getCompilerToken()
{ 
	return compilerToken; 
}

void Action::setCompilerToken(boost::shared_ptr<CompilerToken> ct)
{
	compilerToken = ct; 
}

Action::~Action()
{
}
#include "Action.h"
#include "../Virtual Machine/VirtualMachine.h"

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

CompilerToken* Action::getCompilerToken() 
{ 
	return compilerToken; 
}

void Action::setCompilerToken(CompilerToken* ct) 
{
	compilerToken = ct; 
}

Action::~Action()
{
	if (compilerToken != nullptr){
		delete compilerToken;
	}
}
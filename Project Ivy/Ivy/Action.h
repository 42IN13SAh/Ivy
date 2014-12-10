#pragma once
#include "CompilerToken.h"
class VirtualMachine;

class Action
{
public:
	Action();
	virtual ~Action();
	void setNextAction(Action*);
	void setFalseAction(Action*);
	Action* getNextAction();
	Action* getFalseAction();
	CompilerToken* getCompilerToken();
	void setCompilerToken(CompilerToken*);
private:
	Action* nextAction;
	Action* onFalseAction;
	CompilerToken* compilerToken;
};


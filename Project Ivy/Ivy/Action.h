#pragma once
#include <boost/shared_ptr.hpp>
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
	boost::shared_ptr<CompilerToken> getCompilerToken();
	void setCompilerToken(boost::shared_ptr<CompilerToken>);
private:
	Action* nextAction;
	Action* onFalseAction;
	boost::shared_ptr<CompilerToken> compilerToken;
};


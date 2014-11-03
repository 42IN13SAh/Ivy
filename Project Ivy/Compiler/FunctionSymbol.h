#pragma once
#include <string>
#include "Action.h"

class FunctionSymbol
{
public:
	FunctionSymbol(std::string, int, Action*, Action*);
	~FunctionSymbol();

	Action* getStartAction();
	Action* getEndAction();

	std::string getName();
	int getArgumentNr();

private:
	Action* startAction;
	Action* endAction;

	std::string name;
	int argNr;
};


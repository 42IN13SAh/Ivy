#pragma once
#include <string>
#include "Action.h"

class FunctionSymbol
{
public:
	FunctionSymbol(std::string, int, Action*, Action*, bool);
	~FunctionSymbol();

	Action* getStartAction();
	Action* getEndAction();

	std::string getName();
	int getArgumentNr();

	bool isInternal();

private:
	Action* startAction;
	Action* endAction;

	std::string name;
	int argNr;
	bool internal;
};


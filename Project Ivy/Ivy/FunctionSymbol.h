#pragma once
#include <string>
#include "Action.h"

class SymbolTable;

class FunctionSymbol
{
public:
	FunctionSymbol(std::string, int, Action*, Action*, bool);
	~FunctionSymbol();
	Action* getStartAction();
	Action* getEndAction();
	SymbolTable* getSymbolTable();
	std::string getName();
	int getArgumentNr();
	void setArgumentNr(const int&);
	void setStartAction(Action*);
	void setEndAction(Action*);
	bool isInternal();
private:
	Action* startAction;
	Action* endAction;
	SymbolTable* symbolTable;
	std::string name;
	int argNr;
	bool internal;
};


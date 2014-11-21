#include "FunctionSymbol.h"
#include "SymbolTable.h"

FunctionSymbol::FunctionSymbol(std::string name, int argNr, Action* startAction, Action* endAction, bool internal)
{
	this->name = name;
	this->argNr = argNr;
	this->startAction = startAction;
	this->endAction = endAction;
	this->internal = internal;
	symbolTable = new SymbolTable();
}

FunctionSymbol::~FunctionSymbol()
{
}

Action* FunctionSymbol::getStartAction() { return startAction; }
Action* FunctionSymbol::getEndAction() { return endAction; }
SymbolTable* FunctionSymbol::getSymbolTable() { return symbolTable; }
std::string FunctionSymbol::getName() { return name; }
int FunctionSymbol::getArgumentNr() { return argNr; }
void FunctionSymbol::setStartAction(Action* startAction) { this->startAction = startAction; }
void FunctionSymbol::setEndAction(Action* endAction) { this->endAction = endAction; }
bool FunctionSymbol::isInternal() { return internal; }

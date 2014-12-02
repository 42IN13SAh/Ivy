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
	if (!this->isInternal()){ //Only internal functions have actions that need to be deleted
		Action *currentActionPtr = this->startAction;
		Action *nextActionPtr = currentActionPtr->getNextAction();
		Action *onFalseActionPtr;
		while (nextActionPtr != nullptr && nextActionPtr != this->endAction){
			nextActionPtr = currentActionPtr->getNextAction();
			onFalseActionPtr = currentActionPtr->getFalseAction();
			delete currentActionPtr;
			if (onFalseActionPtr != nullptr){
				delete onFalseActionPtr;
			}
			currentActionPtr = nextActionPtr;
		}
	}
	delete symbolTable;
}

Action* FunctionSymbol::getStartAction() { return startAction; }
Action* FunctionSymbol::getEndAction() { return endAction; }
SymbolTable* FunctionSymbol::getSymbolTable() { return symbolTable; }
std::string FunctionSymbol::getName() { return name; }
int FunctionSymbol::getArgumentNr() { return argNr; }
void FunctionSymbol::setStartAction(Action* startAction) { this->startAction = startAction; }
void FunctionSymbol::setEndAction(Action* endAction) { this->endAction = endAction; }
bool FunctionSymbol::isInternal() { return internal; }

#include "SymbolTable.h"

SymbolTable::SymbolTable(int level, string functionName)
{

}

SymbolTable::SymbolTable()
{

}

SymbolTable::~SymbolTable()
{
	for each(Symbol* s in symbols) {
		delete s;
	}
}


void SymbolTable::addSymbolToTable(string name)
{
	//check if there isn't already an existing variable with the same name, in that case an exception is thrown
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			throw new exception; //TODO: better exception handling
		}
	}

	symbols.push_back(new Symbol(name));
}

void SymbolTable::addSymbolToTable(string name, boost::any value)
{
	//check if there isn't already an existing variable with the same name, in that case an exception is thrown
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			throw new exception; //TODO: better exception handling
		}
	}

	symbols.push_back(new Symbol(name, value));
}


void SymbolTable::updateExistingSymbol(string name, boost::any value)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
		{
			symbol->setValue(value);
			return;
		}
	}

	//symbol was not found in the symboltable
	throw new exception; //TODO: better exception handling
}

bool SymbolTable::hasSymbol(string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
			return true;
	}
	return false;
}

boost::any SymbolTable::getValue(string name)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName() == name)
			return symbol->getValue();
	}
	
	throw new exception; //Symbol not found. TODO: better exception handling
}

void SymbolTable::addFunctionSymbol(FunctionSymbol* fs) {
	if (getFunctionSymbol(fs->getName(), fs->getArgumentNr()) == nullptr) {
		fSymbols.push_back(fs);
	} else {
		throw new exception; // Already exists
	}
}

FunctionSymbol* SymbolTable::getFunctionSymbol(std::string name, int argNr) {
	for each(FunctionSymbol* fs in fSymbols) {
		if (fs->getName() == name && fs->getArgumentNr() == argNr)
			return fs;
	}
	return nullptr;
}
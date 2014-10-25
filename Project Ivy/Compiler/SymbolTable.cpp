#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
}


SymbolTable::~SymbolTable()
{
}


void SymbolTable::addSymbolToTable(string name, boost::any value)
{
	//check if there isn't already an existing variable with the same name, in that case an exception is thrown
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName().compare(name))
		{
			throw new exception; //TODO: better exception handling
		}
	}

	symbols.push_back(new Symbol(name, value));
}

void SymbolTable::addSymbolToTableWithoutValue(string name)
{
	//check if there isn't already an existing variable with the same name, in that case an exception is thrown
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName().compare(name))
		{
			throw new exception; //TODO: better exception handling
		}
	}

	symbols.push_back(new Symbol(name));
}

void SymbolTable::updateExistingSymbol(string name, boost::any value)
{
	for each (Symbol* symbol in symbols)
	{
		if (symbol->getName().compare(name))
		{
			symbol->setValue(value);
		}
	}

	//symbol was not found in the symboltable
	throw new exception; //TODO: better exception handling
}
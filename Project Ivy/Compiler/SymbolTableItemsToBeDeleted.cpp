#include "SymbolTableItemsToBeDeleted.h"


SymbolTableItemsToBeDeleted::SymbolTableItemsToBeDeleted()
{
}


SymbolTableItemsToBeDeleted::~SymbolTableItemsToBeDeleted()
{
}

std::vector<FunctionSymbol *>SymbolTableItemsToBeDeleted::getFunctionSymbols()
{
	return this->functionSymbols;
}

std::vector<Symbol *>SymbolTableItemsToBeDeleted::getSymbols()
{
	return this->symbols;
}

void SymbolTableItemsToBeDeleted::addFunctionSymbol(FunctionSymbol &newItem)
{
	this->functionSymbols.push_back(&newItem);
}

void SymbolTableItemsToBeDeleted::addSymbol(Symbol &newItem)
{
	this->symbols.push_back(&newItem);
}

void SymbolTableItemsToBeDeleted::insertIntoFunctionSymbols(std::vector<FunctionSymbol *> &newItems)
{
	this->functionSymbols.insert(this->functionSymbols.end(), newItems.begin(), newItems.end());
}

void SymbolTableItemsToBeDeleted::insertIntoSymbols(std::vector<Symbol *> &newItems)
{
	this->symbols.insert(this->symbols.end(), newItems.begin(), newItems.end());
}
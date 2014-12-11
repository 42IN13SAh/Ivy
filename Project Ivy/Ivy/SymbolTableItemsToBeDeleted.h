#pragma once
#include <vector>
#include "FunctionSymbol.h"
#include "Symbol.h"

class SymbolTableItemsToBeDeleted
{
public:
	SymbolTableItemsToBeDeleted();
	~SymbolTableItemsToBeDeleted();

	std::vector<FunctionSymbol *>getFunctionSymbols();
	std::vector<Symbol *>getSymbols();
	void addFunctionSymbol(FunctionSymbol &newItem);
	void addSymbol(Symbol &newItem);
	void insertIntoFunctionSymbols(std::vector<FunctionSymbol *> &newItems);
	void insertIntoSymbols(std::vector<Symbol *> &newItems);
private:
	std::vector<FunctionSymbol *>functionSymbols;
	std::vector<Symbol *>symbols;
};


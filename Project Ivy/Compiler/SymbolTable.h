#pragma once
#include <string>
#include <vector>

#include "Symbol.h"
#include "FunctionSymbol.h"
#include "SymbolTableItemsToBeDeleted.h"

class SymbolTable
{
public:
	SymbolTable(int level, string functionName);
	SymbolTable();
	~SymbolTable();
	void addSymbolToTable(std::string name);
	void addSymbolToTable(std::string name, boost::any value);
	void updateExistingSymbol(std::string name, boost::any value);
	void addFunctionSymbol(FunctionSymbol*);
	FunctionSymbol* getFunctionSymbol(std::string, int);
	bool hasSymbol(string);
	boost::any getValue(string);
	std::vector<Symbol *>getAllSymbols();
	std::vector<FunctionSymbol *>getAllFunctionSymbols();
	SymbolTableItemsToBeDeleted *getItemsToDelete(std::vector<FunctionSymbol *>functionSymbolsToSkip = std::vector<FunctionSymbol *>(), std::vector<Symbol *>symbolsToSkip = std::vector<Symbol *>());
private:
	std::vector<Symbol*> symbols;
	std::vector<FunctionSymbol*> fSymbols;
	int level;
	string functionName;
};


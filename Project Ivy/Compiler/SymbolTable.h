#pragma once
#include <string>
#include <vector>

#include "Symbol.h"
#include "FunctionSymbol.h"


class SymbolTable
{
public:
	SymbolTable(int level, string functionName);
	SymbolTable();
	~SymbolTable();

	void addSymbolToTable(std::string name);
	void updateExistingSymbol(std::string name, boost::any value);

	void addFunctionSymbol(FunctionSymbol*);
	FunctionSymbol* getFunctionSymbol(std::string, int);

	bool hasSymbol(string);
	boost::any getValue(string);

private:
	std::vector<Symbol*> symbols;
	std::vector<FunctionSymbol*> fSymbols;
	int level;
	string functionName;
};


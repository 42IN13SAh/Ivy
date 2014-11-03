#pragma once
#include <string>
#include <vector>

#include "Symbol.h"


class SymbolTable
{
public:
	SymbolTable(int level, string functionName);
	SymbolTable();
	~SymbolTable();

	void addSymbolToTable(std::string name);
	void updateExistingSymbol(std::string name, boost::any value);

	bool hasSymbol(string);
	boost::any getValue(string);

private:
	std::vector<Symbol*> symbols;
	int level;
	string functionName;
};


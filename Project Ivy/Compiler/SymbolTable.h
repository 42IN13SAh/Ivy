#pragma once
#include <string>
#include <vector>

#include "Symbol.h"

using namespace std;

class SymbolTable
{
public:
	SymbolTable();
	~SymbolTable();

	void addSymbolToTable(string name, boost::any value);
	void addSymbolToTableWithoutValue(string name);
	void updateExistingSymbol(string name, boost::any value);

private:
	int level;
	string functionName;
	vector<Symbol*> symbols;
};


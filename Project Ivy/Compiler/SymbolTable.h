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

private:
	int level;
	string functionName;
	vector<Symbol> symbols;
};


#pragma once
#include <vector>

#include "SymbolTable.h"
#include "Action.h"

using namespace std;
class Compiler
{
public:
	Compiler();
	~Compiler();

private:
	Action firstAction;
	vector<SymbolTable> symbolTables;
};


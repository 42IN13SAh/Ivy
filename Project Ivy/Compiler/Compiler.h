#pragma once
#include <vector>
#include <list>
#include "SymbolTable.h"
#include "Action.h"

#include "../Tokenizer/Token.h"

using namespace std;
class Compiler
{
public:
	Compiler(list<Token*>);
	~Compiler();

	void compileStatement(Token*);

private:
	list<Token*> tokenList;

	Action firstAction;
	vector<SymbolTable> symbolTables;
};


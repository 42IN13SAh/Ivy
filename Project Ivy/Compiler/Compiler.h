#pragma once
#include <vector>
#include <list>
#include "SymbolTable.h"
#include "Action.h"
#include "DoNothingAction.h"

#include "../Tokenizer/Token.h"

using namespace std;
class Compiler
{
public:
	Compiler(list<Token*>);
	~Compiler();

	void compile();

private:
	list<Token*> tokenList;

	Action* firstAction;
	Action* lastAction;
	vector<SymbolTable> symbolTables;

	std::list<Token*>::iterator tokenIter;
	//Token* currentToken;

	// private functions for compiling
	void compileFunction();
	void compileCodeBlock();
	void compileStatement();
	void compileWhile();
	void compileIf();
	void compileIfElse();
	CompilerToken* compileReturnValue(); // Return must be RValueCompToken

	void compileFirstVars();

	Token* getCurrentToken();
	Token* getNextToken();
	Token* peekNextToken();
	void eraseCurrentToken();
	void resetTokenIter();
};

